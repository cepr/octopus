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

#ifndef REMOTEPROPERTY_H_
#define REMOTEPROPERTY_H_

#ifndef AVR

#include "property.h"
#include "property_address.h"
#include <vector>

/**
 * Property that shadows a remote property by listening to incoming packets.
 *
 * This class is a shadowed version of a remote property. Its name, description,
 * type and value are updated each time a packet coming from the monitored remote property
 * is received.
 *
 * In order to use this class, you should create only one instance using #RemoteProperty and
 * forward all incoming packets to this instance. If an incoming packet concerns the root
 * property, the instance of RemoteProperty will analyze it and update its fields, otherwise
 * it will recursively create the children to handle the received packet.
 *
 * @ingroup COM_STACK
 */
class RemoteProperty: public Property
{
public:
	/**
	 * @brief Constructor.
	 *
	 * @param[in, out] packet  Packet object which will be used to notify property modifications
	 */
	RemoteProperty(Packet* packet);

	/**
	 * @brief Destructor.
	 *
	 * Children are also destroyed recursively.
	 */
	virtual ~RemoteProperty();

	/**
	 * @copydoc Property#getChild()
	 */
	virtual Property* getChild(unsigned char index);

	/**
	 * @copydoc Property#getDescription()
	 */
	virtual const char* getDescription();

	/**
	 * @copydoc Property#getName()
	 */
	virtual const char* getName() const;

	/**
	 * @copydoc Property#getSize()
	 */
	virtual char getSize();

	/**
	 * @copydoc Property#getType()
	 */
	virtual PROPERTY_TYPE getType();

	/**
	 * @copydoc Property#getValue()
	 */
	virtual void getValue(PROPERTY_VALUE& value);

	/**
	 * @copydoc Property#setValue()
	 */
	virtual void setValue(const PROPERTY_VALUE& value);

	/**
	 * @copydoc Property#refresh()
	 */
	virtual void refresh();

	/**
	 * @copydoc PacketListener#onPacketReceived()
	 */
	virtual void onPacketReceived(const unsigned char* data, unsigned char size);

	/**
	 * @copydoc PacketListener#onReadyToSend()
	 */
	virtual bool onReadyToSend(unsigned char* data, unsigned char & size, unsigned char capacity);

protected:
	/**
	 * Creates a new RemoteProperty instance.
	 *
	 * This method is called from #onPacketReceived to create dynamically a new RemoteProperty instance
	 * for a new child. You should override this method if you want to inherit RemoteProperty.
	 */
	virtual RemoteProperty* createChild();

	PROPERTY_INFO mInfoToRequest;
	bool mValueToSend;
	PROPERTY_TYPE mType;
	PROPERTY_VALUE mInputValue;
	PROPERTY_VALUE mOutputValue;
	char* mName;
	char* mDescription;
	std::vector<RemoteProperty*> mChildren;
};

#endif /* AVR */

#endif /* REMOTEPROPERTY_H_ */
