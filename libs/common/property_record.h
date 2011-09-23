#ifndef PROPERTYRECORD_H
#define PROPERTYRECORD_H

#include "Property.h" // Base class: Property

/**
 * \brief Base abstract class for all properties records.
 */
class PropertyRecord : public Property {

public:

	PROPERTY_TYPE getType() {
        return PROPERTY_TYPE_VOID;
	}

    char getSize() {
        return 0;
    }
    
	virtual void getValue(PROPERTY_VALUE & value){
    }

	virtual void setValue(const PROPERTY_VALUE & value){
	}
};

#endif // PROPERTYRECORD_H
