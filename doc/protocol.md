
# Octopus control and telemetry protocol

11 73 F1 1B 84 1B 80 1b 8a
xon
   start
      report
         esc
            PROPERTY_INFO_TYPE
               esc
                  PROPERTY_TYPE_VOID
                     esc
                        stop

Packet:

	static const unsigned char ESCAPE	= 0x80;
	static const unsigned char START	= 's'; // 0x73
	static const unsigned char STOP		= '\n'; // 0x0A


Property:

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

Command report:

	static const PROPERTY_INFO PROPERTY_INFO_NAME           = (1<<0);
	static const PROPERTY_INFO PROPERTY_INFO_DESCRIPTION    = (1<<1);
	static const PROPERTY_INFO PROPERTY_INFO_TYPE           = (1<<2);
	static const PROPERTY_INFO PROPERTY_INFO_VALUE          = (1<<3);
	static const PROPERTY_INFO PROPERTY_INFO_CHILDREN       = (1<<4);	// reserved for dynamic creation of children
