/*
 * Copyright 2012 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "remote_property.h"
#include <string.h>

RemoteProperty::RemoteProperty(Packet* packet) :
	Property(packet),
	mType(PROPERTY_TYPE_VOID),
	mName(0),
	mDescription(0),
	mInfoToRequest(PROPERTY_INFO_NAME | PROPERTY_INFO_DESCRIPTION | PROPERTY_INFO_TYPE | PROPERTY_INFO_VALUE | PROPERTY_INFO_CHILDREN),
	mValueToSend(false)
{
	mInputValue.clear();
	mOutputValue.clear();
	if (packet) {
		packet->requestToSend();
	}
}

RemoteProperty::~RemoteProperty()
{
	if (mListener) {
		mListener->onPropertyDeleted(this);
	}
}

Property* RemoteProperty::getChild(unsigned char index)
{
	if (index < mChildren.size()) {
		return mChildren[index];
	} else {
		return 0;
	}
}

const char* RemoteProperty::getName() const
{
	// TODO getName() should return 0 and application should handle this use case
	return mName ? mName : "Untitled";
}

const char* RemoteProperty::getDescription()
{
	// TODO getDescription() should return 0 and application should handle this use case
	return mDescription ? mDescription : "";
}

char RemoteProperty::getSize()
{
	switch(mType) {
	case PROPERTY_TYPE_VOID:
		return 0;
	case PROPERTY_TYPE_BOOL:
	case PROPERTY_TYPE_S8:
	case PROPERTY_TYPE_U8:
		return 1;
	case PROPERTY_TYPE_U16:
	case PROPERTY_TYPE_S16:
		return 2;
	}
}

PROPERTY_TYPE RemoteProperty::getType()
{
	return mType;
}

void RemoteProperty::getValue(PROPERTY_VALUE& value)
{
	value = mInputValue;
}

void RemoteProperty::setValue(const PROPERTY_VALUE& value)
{
	mOutputValue = value;
	mValueToSend = true;
	if (mPacket) {
		mPacket->requestToSend();
	}
}

void RemoteProperty::refresh()
{
	// Delete all children
	std::vector<RemoteProperty*>::iterator i;
	for (i = mChildren.begin(); i != mChildren.end(); ++i) {
		RemoteProperty* p = *i;
		delete p;
	}
	mChildren.clear();
	
	std::vector<RemoteProperty*>::size_type toto = mChildren.size();

	// Restore default state
	mType = PROPERTY_TYPE_VOID;
	delete mName;
	mName = 0;
	delete mDescription;
	mDescription = 0;
	mInfoToRequest = PROPERTY_INFO_NAME | PROPERTY_INFO_DESCRIPTION | PROPERTY_INFO_TYPE | PROPERTY_INFO_VALUE | PROPERTY_INFO_CHILDREN;
	mValueToSend = false;
	mInputValue.clear();
	mOutputValue.clear();
	if (mPacket) {
		mPacket->requestToSend();
	}
}

void RemoteProperty::onPacketReceived(const unsigned char* data, unsigned char size)
{
	if (size > 0) {
		PROPERTY_INFO what_changed = 0;

		if (data[0] < CMD_BROADCAST) {
			// The packet is for one of our children

			// Resize children array if necessary
			if (data[0] >= mChildren.size()) {
				mChildren.resize(data[0]+1);
			}

			// Create a new child if necessary
			if (!mChildren[data[0]]) {
				mChildren[data[0]] = new RemoteProperty(mPacket);
				//what_changed |= PROPERTY_INFO_CHILDREN;
				if (mListener) {
					mListener->onNewChild(this, mChildren[data[0]], data[0]);
				}
			}

			mChildren[data[0]]->onPacketReceived(&data[1], size-1);
		} else if (data[0] == CMD_BROADCAST) {
			// The packet is for all children
			// TODO Handle broadcasted packets in remote_property
		} else {
			// The packet is for this property
			if ((data[0] == CMD_REPORT) && (size >= 1 + sizeof(PROPERTY_INFO))) {
				// Extract information type
				memcpy(&what_changed, &data[1], sizeof(PROPERTY_INFO));
				data += 1 + sizeof(PROPERTY_INFO);
				size -= 1 + sizeof(PROPERTY_INFO);
				// Extract information according to its type
				switch(what_changed) {
				case PROPERTY_INFO_TYPE:
					mType = PROPERTY_TYPE_VOID;
					if (size <= sizeof(PROPERTY_TYPE)) {
						memcpy(&mType, &data[0], size);
					}
					break;
				case PROPERTY_INFO_NAME:
					delete mName;
					mName = new char[size+1];
					memcpy(mName, &data[0], size);
					mName[size] = '\0';
					break;
				case PROPERTY_INFO_DESCRIPTION:
					delete mDescription;
					mDescription = new char[size+1];
					memcpy(mDescription, &data[0], size);
					mDescription[size] = '\0';
					break;
				case PROPERTY_INFO_VALUE:
					if (size > sizeof(PROPERTY_VALUE)) {
						size = sizeof(PROPERTY_VALUE);
					}
					mInputValue.clear();
					memcpy(&mInputValue, &data[0], size);
					break;
				}
			}
		}

		// Notify listener about property change
		if (what_changed) {
			mInfoToRequest &= ~what_changed;
			if (mListener) {
				mListener->onPropertyChanged(this, what_changed);
			}
		}
	}
}

bool RemoteProperty::onReadyToSend(unsigned char* data, unsigned char & size, unsigned char capacity)
{
	if (size < capacity) {

		// Property has been modified on the host and its value must be sent to the device
		if (mValueToSend) {
			char data_size = getSize();
			if (size + 1 + sizeof(PROPERTY_INFO) + data_size <= capacity) {
				mValueToSend = false;
				// Append CMD_SET to packet
				data[size++] = CMD_SET;
				// Append PROPERTY_INFO_VALUE to packet
				memcpy(&data[size], &PROPERTY_INFO_VALUE, sizeof(PROPERTY_INFO));
				size += sizeof(PROPERTY_INFO);
				// Append value to packet
				memcpy(&data[size], &mOutputValue, data_size);
				size += data_size;
				return true;
			}
		}

		// If any information is missing, let's request it now
		if (mInfoToRequest) {
			PROPERTY_INFO std_info = mInfoToRequest & (PROPERTY_INFO_TYPE | PROPERTY_INFO_NAME | PROPERTY_INFO_DESCRIPTION | PROPERTY_INFO_VALUE);
			if (std_info) {
				if (size + 1 + sizeof(PROPERTY_INFO) <= capacity) {
					mInfoToRequest &= ~std_info;
					// Append CMD_GET to packet
					data[size++] = CMD_GET;
					// Append PROPERTY_INFO mask to packet
					memcpy(&data[size], &std_info, sizeof(PROPERTY_INFO));
					size += sizeof(PROPERTY_INFO);
					return true;
				}
			} else if (mInfoToRequest & PROPERTY_INFO_CHILDREN) {
				if (size + 1 + 1 + sizeof(PROPERTY_INFO) <= capacity) {
					mInfoToRequest &= ~PROPERTY_INFO_CHILDREN;
					// Append broadcast address to packet
					data[size++] = CMD_BROADCAST;
					// Append CMD_GET to packet
					data[size++] = CMD_GET;
					// Append PROPERTY_INFO_NAME to packet
					memcpy(&data[size], &PROPERTY_INFO_NAME, sizeof(PROPERTY_INFO));
					size += sizeof(PROPERTY_INFO);
					return true;
				}
			}
		}

		// Do the same recursively for all children
		int i;
		for (i = 0; i < mChildren.size(); i++) {
			RemoteProperty* prop = mChildren[i];
			if (prop) {
				data[size++] = (unsigned char)i;
				if (prop->onReadyToSend(data, size, capacity)) {
					return true;
				}
				size--;
			}
		}
	}

	return false;
}
