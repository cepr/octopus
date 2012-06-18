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

#include "local_property.h"
#include <string.h>

LocalProperty::LocalProperty(Packet* packet) :
	Property(packet),
	mInfoToReport(PROPERTY_INFO_NAME | PROPERTY_INFO_DESCRIPTION | PROPERTY_INFO_TYPE | PROPERTY_INFO_VALUE)
{
	if (mPacket) {
		mPacket->requestToSend();
	}
}

void LocalProperty::onPacketReceived(const unsigned char* data, unsigned char size)
{
	if (size > 0) {
		if (data[0] < CMD_BROADCAST) {
			// The packet is for one of one child
			Property* prop = getChild(data[0]);
			if (prop) {
				prop->onPacketReceived(&data[1], size-1);
			}
		} else if (data[0] == CMD_BROADCAST) {
			// The packet is for all children
			unsigned char i;
			Property* prop;
			for (i=0; (prop = getChild(i)) != 0; i++) {
				prop->onPacketReceived(&data[1], size-1);
			}
		} else {
			// The packet is for us
			if (size >= 1 + sizeof(PROPERTY_INFO)) {
				unsigned char cmd = data[0];
				PROPERTY_INFO info;
				memcpy(&info, &data[1], sizeof(PROPERTY_INFO));
				if (cmd == CMD_GET) {
					mInfoToReport |= info;
				} else if ((cmd == CMD_SET) && (info == PROPERTY_INFO_VALUE)) {
					char data_size = getSize();
					if (size >= 1 + sizeof(PROPERTY_INFO) + data_size) {
						PROPERTY_VALUE value;
						memcpy(&value, &data[2], data_size);
						setValue(value);
						// The next line is optional, it triggers an acknowledge
						mInfoToReport |= PROPERTY_INFO_VALUE;
					}
				}
			}

			if (mPacket && mInfoToReport) {
				mPacket->requestToSend();
			}
		}
	}
}

bool LocalProperty::onReadyToSend(unsigned char* data, unsigned char & size, unsigned char capacity)
{
	if (size < capacity) {

		// Report any requested information
		if (mInfoToReport & PROPERTY_INFO_VALUE) {
			char data_size = getSize();
			if (size + 1 + sizeof(PROPERTY_INFO) + data_size <= capacity) {
				mInfoToReport &= ~PROPERTY_INFO_VALUE;
				// Append CMD_REPORT to packet
				data[size++] = CMD_REPORT;
				// Append PROPERTY_INFO_VALUE to packet
				memcpy(&data[size], &PROPERTY_INFO_VALUE, sizeof(PROPERTY_INFO));
				size+=sizeof(PROPERTY_INFO);
				// Append value to packet
				PROPERTY_VALUE value;
				getValue(value);
				memcpy(&data[size], &value, data_size);
				size+=data_size;
				return true;
			}
		} else if (mInfoToReport & PROPERTY_INFO_NAME) {
			const char* name = getName();
			char data_size = strlen(name);
			if (size + 1 + sizeof(PROPERTY_INFO) + data_size <= capacity) {
				mInfoToReport &= ~PROPERTY_INFO_NAME;
				// Append CMD_REPORT to packet
				data[size++] = CMD_REPORT;
				// Append PROPERTY_INFO_NAME to packet
				memcpy(&data[size], &PROPERTY_INFO_NAME, sizeof(PROPERTY_INFO));
				size+=sizeof(PROPERTY_INFO);
				// Append name to packet
				memcpy(&data[size], name, data_size);
				size+=data_size;
				return true;
			}
		} else if (mInfoToReport & PROPERTY_INFO_DESCRIPTION) {
			const char* desc = getDescription();
			char data_size = strlen(desc);
			if (size + 1 + sizeof(PROPERTY_INFO) + data_size <= capacity) {
				mInfoToReport &= ~PROPERTY_INFO_DESCRIPTION;
				// Append CMD_REPORT to packet
				data[size++] = CMD_REPORT;
				// Append PROPERTY_INFO_DESCRIPTION to packet
				memcpy(&data[size], &PROPERTY_INFO_DESCRIPTION, sizeof(PROPERTY_INFO));
				size+=sizeof(PROPERTY_INFO);
				// Append description to packet
				memcpy(&data[size], desc, data_size);
				size+=data_size;
				return true;
			}
		} else if (mInfoToReport & PROPERTY_INFO_TYPE) {
			if (size + 1 + sizeof(PROPERTY_INFO) + 1 <= capacity) {
				mInfoToReport &= ~PROPERTY_INFO_TYPE;
				// Append CMD_REPORT to packet
				data[size++] = CMD_REPORT;
				// Append PROPERTY_INFO_TYPE to packet
				memcpy(&data[size], &PROPERTY_INFO_TYPE, sizeof(PROPERTY_INFO));
				size+=sizeof(PROPERTY_INFO);
				// Append type to packet
				data[size++] = (unsigned char)getType();
				return true;
			}
		}

		// For each child, recursively call onReadyToSend() to cover every property of the tree
		// TODO thread d'envoi par looper et event en liste chainée !
		unsigned char i=0;
		Property* prop;
		while((prop = getChild(i)) != 0) {
			data[size++] = i;
			if (prop->onReadyToSend(data, size, capacity)) {
				return true;
			}
			size--;
			i++;
		}
	}

	return false;
}

void LocalProperty::refresh()
{
}
