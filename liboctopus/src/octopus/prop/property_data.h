/*
 * Copyright 2010-2012 Cedric Priscal
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

#ifndef PROPERTYDATA_H
#define PROPERTYDATA_H

#include "local_property.h"

/**
 * \brief Base abstract class for all properties containing a data variable, as opposite to a PropertyRecord.
 * \see PropertyBoolean, PropertyU8, PropertyS8, PropertyU16, PropertyS16.
 */
template <class T> 
class PropertyData : public LocalProperty {

protected:
    T mValue;

protected:
	/**
	 * \brief Constructor.
	 */
	PropertyData(T value, Packet* packet) : LocalProperty(packet), mValue(value) {
    }

private:
    // Property pure virtual inherited functions.
	Property* getChild(unsigned char index)	{
        return (Property*)0;
	}

public:
    void setValue(const PROPERTY_VALUE & value) {
        if ((T)value != mValue) {
            mValue = value;
#ifdef __AVR
            if (mListener) {
                mListener->onPropertyChanged(this, PROPERTY_INFO_VALUE, PropertyListener::ORIGIN_REMOTE);
            }
#else
            std::list<PropertyListener*>::iterator it;
            for (it = mListeners.begin(); it != mListeners.end(); ++it) {
            	(*it)->onPropertyChanged(this, PROPERTY_INFO_VALUE, PropertyListener::ORIGIN_REMOTE);
            }
#endif
        }
    }
    void getValue(PROPERTY_VALUE & value) { value = mValue; }
    char getSize() { return sizeof(T); }
    PROPERTY_TYPE getType() { return PROPERTY_TYPE(T); }
    operator T() {
        return mValue;
    }
    T operator=(T value) {
        if (value != mValue) {
            mValue = value;
#ifdef __AVR
            if (mListener) {
                mListener->onPropertyChanged(this, PROPERTY_INFO_VALUE, PropertyListener::ORIGIN_LOCAL);
            }
#else
            std::list<PropertyListener*>::iterator it;
            for (it = mListeners.begin(); it != mListeners.end(); ++it) {
            	(*it)->onPropertyChanged(this, PROPERTY_INFO_VALUE, PropertyListener::ORIGIN_LOCAL);
            }
#endif
        }
        return mValue;
    }
    const T operator++(int) {
        mValue++;
        return mValue;
    }
    const T operator--(int) {
        mValue--;
        return mValue;
    }
};

/**
 * \brief Abstract base class for all properties of type boolean.
 * When extending this class, you should implement getName() and getDescription().
 */
typedef PropertyData<bool> PropertyBoolean;

/**
 * \brief Abstract base class for all properties of type unsigned char.
 * When extending this class, you should implement getName() and getDescription().
 */
typedef PropertyData<unsigned char> PropertyU8;

/**
 * \brief Abstract base class for all properties of type signed char.
 * When extending this class, you should implement getName() and getDescription().
 */
typedef PropertyData<signed char> PropertyS8;

/**
 * \brief Abstract base class for all properties of type unsigned short.
 * When extending this class, you should implement getName() and getDescription().
 */
typedef PropertyData<unsigned short> PropertyU16;

/**
 * \brief Abstract base class for all properties of type signed short.
 * When extending this class, you should implement getName() and getDescription().
 */
typedef PropertyData<signed short> PropertyS16;

#endif // PROPERTYDATA_H
