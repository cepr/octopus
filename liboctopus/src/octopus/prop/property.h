/*
 * Copyright 2010-2011 Cedric Priscal
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

#ifndef PROPERTY_H_
#define PROPERTY_H_

#ifndef AVR
#include <list>
#endif

/**
 * @brief Property type
 *
 * This enumeration defines the possible types of a property.
 * @see Property#getType()
 */
typedef enum {
    PROPERTY_TYPE_VOID,	/**< The property has either no value or its type has not been discovered by remote property. */
    PROPERTY_TYPE_BOOL,	/**< The property holds a boolean value. */
    PROPERTY_TYPE_U16,	/**< The property holds an unsigned 16 bits integer. */
    PROPERTY_TYPE_S16,	/**< The property holds an unsigned 16 bits integer. */
    PROPERTY_TYPE_S8,	/**< The property holds a signed 8 bits integer. */
    PROPERTY_TYPE_U8	/**< The property holds an unsigned 8 bits integer. */
} PROPERTY_TYPE;

template <class T>
PROPERTY_TYPE _getType();
#define PROPERTY_TYPE(T) _getType<T>()

template <> inline PROPERTY_TYPE _getType<bool>()            { return PROPERTY_TYPE_BOOL; }
template <> inline PROPERTY_TYPE _getType<unsigned short>()  { return PROPERTY_TYPE_U16; }
template <> inline PROPERTY_TYPE _getType<signed short>()    { return PROPERTY_TYPE_S16; }
template <> inline PROPERTY_TYPE _getType<signed char>()     { return PROPERTY_TYPE_S8; }
template <> inline PROPERTY_TYPE _getType<unsigned char>()   { return PROPERTY_TYPE_U8; }

/**
 * @brief Property value
 *
 * You must use Property::getType() to get the valid property type.
 */
typedef union uPROPERTY_VALUE {
	char            boolean;    /**< Valid for PROPERTY_TYPE_BOOL. */
	unsigned short  u16;        /**< Valid for PROPERTY_TYPE_U16. */
	signed short    s16;        /**< Valid for PROPERTY_TYPE_S16. */
	unsigned char   u8;         /**< Valid for PROPERTY_TYPE_U8. */
	signed char     s8;         /**< Valid for PROPERTY_TYPE_S8. */

    // Constructor
	uPROPERTY_VALUE()                     : u16(0)         {}
	uPROPERTY_VALUE(bool           value) : boolean(value) {}
	uPROPERTY_VALUE(unsigned short value) : u16(value)     {}
	uPROPERTY_VALUE(signed   short value) : s16(value)     {}
	uPROPERTY_VALUE(unsigned char  value) : u8(value)      {}
	uPROPERTY_VALUE(signed   char  value) : s8(value)      {}

    // Methods
	void clear() { u16 = 0; }

    // Operator=
    inline bool operator=(bool value) { boolean = value; return value; }
    inline unsigned short operator=(unsigned short value) { return u16 = value; }
    inline signed short operator=(signed short value) { return s16 = value; }
    inline unsigned char operator=(unsigned char value) { return u8 = value; }
    inline signed char operator=(signed char value) { return s8 = value; }

    // Cast
    inline operator bool() const { return boolean; }
    inline operator unsigned short() const { return u16; }
    inline operator signed short() const { return s16; }
    inline operator unsigned char() const { return u8; }
    inline operator signed char() const { return s8; }
} PROPERTY_VALUE;

/**
 * @brief Property information type
 *
 * Bit field of the different kinds of information that are stored into a property.
 */
typedef unsigned char PROPERTY_INFO;

class Property;

#include "property_listener.h"
#include "packet_listener.h"
#include "packet.h"

/**
 * @brief Base abstract class for all properties
 *
 * @ingroup COM_STACK
 */
class Property: public PacketListener
{

public:

	/**
	 * @brief Constructor
	 *
	 * @param[in, out] packet Packet object which will be used to notify property modifications
	 */
	Property(Packet* packet);

	/**
	 * @brief Register a listener
	 *
	 * @param[in] listener Listener to be called when the property is modified
	 *
	 * @a listener will be called each time a new piece of information is received
	 * from the remote property, like its name, description, type or value.
	 *
	 * @warning When this class is built for AVR, you can register only one listener.
	 *
	 * @see ::unregisterListener()
	 */
	void registerListener(PropertyListener *listener);

	/**
	 * @brief Unregister a listener
	 *
	 * @param[in] listener Listener
	 *
	 * @see ::registerListener()
	 */
	void unregisterListener(PropertyListener *listener);

	/**
	 * @brief Get the type of the property.
	 * @return Type of the property.
	 */
	virtual PROPERTY_TYPE getType() = 0;

	/**
	 * @brief Get the size of the property.
	 * @return Size of the property.
	 */
	virtual char getSize() = 0;

	/**
	 * @brief Get the name of the property.
	 * @return This method returns the name of the property in UTF8 format.
	 */
	virtual const char* getName() const = 0;

	/**
	 * @brief Get the description of the property.
	 * @return Description of the property.
	 */
	virtual const char* getDescription() = 0;

	/**
	 * @brief Get the value of the property
	 *
	 * @param[out] value Value of the property
	 *
	 * You must call getType() to identify the type of the property, and
	 * then read the correct union member.
	 */
	virtual void getValue(PROPERTY_VALUE & value) = 0;

	/**
	 * @brief Set the value of the property.
	 * @param[in] value Pointer to the new value.
	 * setValue() may ignore this call if this property is read only.
	 */
	virtual void setValue(const PROPERTY_VALUE & value) = 0;

	/**
	 * @brief Get a child of this property.
	 * @param[in] index property index.
	 * @return A pointer to the child, or 0 if the index is out of bound.
	 */
	virtual Property* getChild(unsigned char index) = 0;

	/**
	 * @brief Refresh property and its progeny
	 */
	virtual void refresh() = 0;

	static const PROPERTY_INFO PROPERTY_INFO_NAME           = (1<<0);
	static const PROPERTY_INFO PROPERTY_INFO_DESCRIPTION    = (1<<1);
	static const PROPERTY_INFO PROPERTY_INFO_TYPE           = (1<<2);
	static const PROPERTY_INFO PROPERTY_INFO_VALUE          = (1<<3);
	static const PROPERTY_INFO PROPERTY_INFO_CHILDREN       = (1<<4);	// reserved for dynamic creation of children

protected:
	// Bytes below 0xf0 are considered as part of the property address
	static const unsigned char CMD_BROADCAST		= 0xf0;
	// Bytes higher than 0xf0 are for commands
	static const unsigned char CMD_REPORT			= 0xf1;
	static const unsigned char CMD_GET 				= 0xf2;
	static const unsigned char CMD_SET 				= 0xf3;
	// Reserved for future use commands
	static const unsigned char CMD_RESERVED_F4		= 0xf4;
	static const unsigned char CMD_RESERVED_F5		= 0xf5;
	static const unsigned char CMD_RESERVED_F6		= 0xf6;
	static const unsigned char CMD_RESERVED_F7		= 0xf7;
	// Free to use commands
	static const unsigned char CMD_CUSTOM_F8		= 0xf8;
	static const unsigned char CMD_CUSTOM_F9		= 0xf9;
	static const unsigned char CMD_CUSTOM_FA		= 0xfa;
	static const unsigned char CMD_CUSTOM_FB		= 0xfb;
	static const unsigned char CMD_CUSTOM_FC		= 0xfc;
	static const unsigned char CMD_CUSTOM_FD		= 0xfd;
	static const unsigned char CMD_CUSTOM_FE		= 0xfe;
	static const unsigned char CMD_CUSTOM_FF		= 0xff;

	Packet*	mPacket;
public:
#ifdef AVR
	PropertyListener *mListener;
#else
    std::list<PropertyListener*> mListeners;
#endif
};

#endif /* PROPERTY_H_ */
