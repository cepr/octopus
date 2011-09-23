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

class Property;

#include "PropertyListener.h"

/**
 * \brief Property types
 */
typedef enum {
    PROPERTY_TYPE_INVALID,    /**< The property type has not been received from remote device.*/
    PROPERTY_TYPE_UNKNOWN,    /**< The property type has not yet been defined. */
    PROPERTY_TYPE_VOID,      /**< The property has no value, but some children. */
    PROPERTY_TYPE_BOOL,      /**< The property holds a boolean value. */
    PROPERTY_TYPE_U16,       /**< The property holds an unsigned 16 bits integer. */
    PROPERTY_TYPE_S16,       /**< The property holds an unsigned 16 bits integer. */
    PROPERTY_TYPE_S8,       /**< The property holds a signed 8 bits integer. */
    PROPERTY_TYPE_U8
} PROPERTY_TYPE;

/**
 * \brief Property value
 *
 * You must use Property::getType() to get the valid property type.
 */
typedef union {
    char            boolean;    /**< Valid for PROPERTY_TYPE_BOOL. */
    unsigned short  u16;        /**< Valid for PROPERTY_TYPE_U16. */
    signed short    s16;        /**< Valid for PROPERTY_TYPE_S16. */
    unsigned char   u8;         /**< Valid for PROPERTY_TYPE_U8. */
    signed char     s8;         /**< Valid for PROPERTY_TYPE_S8. */
} PROPERTY_VALUE;

/**
 * \brief Base abstract class for all properties.
 */
class Property {

private:

public:
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
     * @return Name of the property.
     */
    virtual const char* getName() = 0;

    /**
     * @brief Get the description of the property.
     * @return Description of the property.
     */
    virtual const char* getDescription() = 0;

    /**
     * \brief Get the value of the property
     *
     * \param[out] value Value of the property
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
};

#endif /* PROPERTY_H_ */
