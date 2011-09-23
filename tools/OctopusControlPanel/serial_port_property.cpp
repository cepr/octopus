#include "serial_port_property.h"

// constructor
SerialPortProperty::SerialPortProperty(const char* device)
    : mSerialPort(device),
      mPacket(&mSerialPort),
      mBridge(&mPacket),
      mRootProperty(&mRootAddress, &mBridge)
{
	if (mDevice) {
		mDevice = device;
	} else {
		mDevice = "stdin/stdout";
	}
}

// destructor
SerialPortProperty::~SerialPortProperty() {
    // TODO
}

// Property inherited virtual functions

const char* SerialPortProperty::getName() {
    return mDevice;
}

const char* SerialPortProperty::getDescription() {
    return "Serial port";
}

Property* SerialPortProperty::getChild(unsigned char index) {
    if (index == 0) {
        return &mRootProperty;
    } else {
        return NULL;
    }
}
