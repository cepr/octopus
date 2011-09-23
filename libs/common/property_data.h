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

#ifndef PROPERTYDATA_H
#define PROPERTYDATA_H

#include "Property.h" // Base class: Property

/**
 * \brief Base abstract class for all properties containing a data variable, as opposite to a PropertyRecord.
 * \see PropertyBoolean, PropertyU8, PropertyS8, PropertyU16, PropertyS16.
 */
template <class T> 
class PropertyData : public Property {

protected:
    T mValue;

protected:
	/**
	 * \brief Constructor.
	 */
	PropertyData(T value) : mValue(value) {
    }

private:
    // Property pure virtual inherited functions.
	Property* getChild(unsigned char index)	{
        return (Property*)0;
	}

public:
    operator T() {
        return mValue;
    }
    T operator=(T value) {
        return mValue = value;
    }
    const T operator++(int) {
        mValue++;
        return *this;
    }
    const T operator--(int) {
        mValue--;
        return *this;
    }
};

/**
 * \brief Abstract base class for all properties of type boolean.
 * When extending this class, you should implement getName() and getDescription().
 */
class PropertyBoolean: public PropertyData<bool> {
public:
    PropertyBoolean(bool value = false) : PropertyData<bool>(value){}
    PROPERTY_TYPE getType() { return PROPERTY_TYPE_BOOL; }
    void getValue(PROPERTY_VALUE & value) { value.boolean = mValue; }
    virtual void setValue(const PROPERTY_VALUE & value) { mValue = value.boolean; }
    char getSize() { return 1; }
    using PropertyData<bool>::operator =;
    using PropertyData<bool>::operator ++;
    using PropertyData<bool>::operator --;
};

/**
 * \brief Abstract base class for all properties of type unsigned char.
 * When extending this class, you should implement getName() and getDescription().
 */
class PropertyU8: public PropertyData<unsigned char> {
public:
    PropertyU8(unsigned char value = 0) : PropertyData<unsigned char>(value){}
    PROPERTY_TYPE getType() { return PROPERTY_TYPE_U8; }
    void getValue(PROPERTY_VALUE & value) { value.u8 = mValue; }
    virtual void setValue(const PROPERTY_VALUE & value) { mValue = value.u8; }
    char getSize() { return 1; }
    using PropertyData<unsigned char>::operator =;
    using PropertyData<unsigned char>::operator ++;
    using PropertyData<unsigned char>::operator --;
};

/**
 * \brief Abstract base class for all properties of type signed char.
 * When extending this class, you should implement getName() and getDescription().
 */
class PropertyS8: public PropertyData<signed char> {
public:
    PropertyS8(signed char value = 0) : PropertyData<signed char>(value){}
    PROPERTY_TYPE getType() { return PROPERTY_TYPE_S8; }
    void getValue(PROPERTY_VALUE & value) { value.s8 = mValue; }
    virtual void setValue(const PROPERTY_VALUE & value) { mValue = value.s8; }
    char getSize() { return 1; }
    using PropertyData<signed char>::operator =;
    using PropertyData<signed char>::operator ++;
    using PropertyData<signed char>::operator --;
};

/**
 * \brief Abstract base class for all properties of type unsigned short.
 * When extending this class, you should implement getName() and getDescription().
 */
class PropertyU16: public PropertyData<unsigned short> {
public:
    PropertyU16(unsigned short value = 0) : PropertyData<unsigned short>(value){}
    PROPERTY_TYPE getType() { return PROPERTY_TYPE_U16; }
    void getValue(PROPERTY_VALUE & value) { value.u16 = mValue; }
    virtual void setValue(const PROPERTY_VALUE & value) { mValue = value.u16; }
    char getSize() { return 2; }
    using PropertyData<unsigned short>::operator =;
    using PropertyData<unsigned short>::operator ++;
    using PropertyData<unsigned short>::operator --;
};

/**
 * \brief Abstract base class for all properties of type signed short.
 * When extending this class, you should implement getName() and getDescription().
 */
class PropertyS16: public PropertyData<signed short> {
public:
    PropertyS16(signed short value = 0) : PropertyData<signed short>(value){}
    PROPERTY_TYPE getType() { return PROPERTY_TYPE_S16; }
    void getValue(PROPERTY_VALUE & value) { value.s16 = mValue; }
    virtual void setValue(const PROPERTY_VALUE & value) { mValue = value.s16; }
    char getSize() { return 2; }
    using PropertyData<signed short>::operator =;
    using PropertyData<signed short>::operator ++;
    using PropertyData<signed short>::operator --;
};

#endif // PROPERTYDATA_H
