#ifndef PROPERTYRECORD_H
#define PROPERTYRECORD_H

#include "local_property.h"

/**
 * \brief Base abstract class for all properties records.
 */
class PropertyRecord : public LocalProperty {

public:

	PropertyRecord(Packet* packet) : LocalProperty(packet) {
	}

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
