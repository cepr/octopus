#ifndef SERIALPORTPROPERTY_H
#define SERIALPORTPROPERTY_H

#include "Property.h" // Base class: Property
#include "property_record.h"
#include "LinuxSerialPort.h"
#include "Packet.h"
#include "PropertyPacket.h"
#include "PropertyAddress.h"
#include "LinuxRemoteProperty.h"
#include <wx/string.h>

class SerialPortProperty : public PropertyRecord {

public:
    SerialPortProperty(const char* device);
    ~SerialPortProperty();

public:
    const char* getName();
    const char* getDescription();
    Property* getChild(unsigned char index);

private:
    wxCharBuffer            mDevice;
    LinuxSerialPort 		mSerialPort;
    Packet 					mPacket;
    PropertyPacket 			mBridge;
    PropertyAddress         mRootAddress;
    LinuxRemoteProperty		mRootProperty;
};

#endif // SERIALPORTPROPERTY_H
