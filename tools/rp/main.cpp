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

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "LinuxSerialPort.h"
#include "Packet.h"
#include "LinuxRemoteProperty.h"
#include "PropertyPacket.h"

static const char* type_to_string(PROPERTY_TYPE type) {
	switch (type) {
	case PROPERTY_TYPE_VOID:		return "void";
	case PROPERTY_TYPE_BOOL:		return "bool";
	case PROPERTY_TYPE_U16:			return "u16";
	case PROPERTY_TYPE_S16:			return "s16";
	case PROPERTY_TYPE_U8:			return "u8";
	case PROPERTY_TYPE_S8:			return "s8";
	default:                		return "?";
	}
}

static const char* value_to_string(PROPERTY_TYPE type, PROPERTY_VALUE value) {
	static char buffer[32];
	switch(type) {

	case PROPERTY_TYPE_VOID:
		return "";

	case PROPERTY_TYPE_BOOL:
		return value.boolean ? "true" : "false";

	case PROPERTY_TYPE_U16:
		sprintf(buffer, "%d", (int)value.u16);
		return buffer;

	case PROPERTY_TYPE_S16:
		sprintf(buffer, "%d", (int)value.s16);
		return buffer;

	case PROPERTY_TYPE_U8:
		sprintf(buffer, "%d", (int)value.u8);
		return buffer;

	case PROPERTY_TYPE_S8:
		sprintf(buffer, "%d", (int)value.s8);
		return buffer;

	default:
		return "?";
	}
}

static PROPERTY_VALUE string_to_value(PROPERTY_TYPE type, const char* str) {
	PROPERTY_VALUE value;
	value.u16 = 0;
	switch(type) {
	case PROPERTY_TYPE_BOOL:
		value.boolean = (!strcmp(str, "true")) ? 1 : 0;
		break;

	case PROPERTY_TYPE_U16:
		value.u16 = atoi(str);
		break;

	case PROPERTY_TYPE_S16:
		value.s16 = atoi(str);
		break;

	default:
		printf("Invalid type for command set.\n");
	}
	return value;
}

/*
 * // description
 * type name = value {
 *     // description
 *     type name = value;
 * }
 */
static void print_property(Property *prop, int level) {

	const char* name = prop->getName();
	const char* desc = prop->getDescription();
	PROPERTY_TYPE type = prop->getType();
	PROPERTY_VALUE value;
	prop->getValue(value);

	if (type == PROPERTY_TYPE_VOID) {
		printf(	"%*s// %s\n"
				"%*s%s",
				level * 4, "", desc,
				level * 4, "", name
		);
	} else {
		printf(	"%*s// %s\n"
				"%*s%s %s = %s",
				level * 4, "", desc,
				level * 4, "", type_to_string(type), name, value_to_string(type, value)
		);
	}

	int i=0;
	Property* child;
	bool has_child = false;
	while((child = prop->getChild(i)) != 0) {
		if (!has_child) {
			has_child = true;
			printf(" {\n");
		}
		print_property(child, level+1);
		i++;
	}

	if (has_child) {
		printf( "%*s}\n", level * 4, "");
	} else {
		printf(";\n");
	}
}

static void usage() {
	printf("rp <print|get|set> <address> [value]\n");
}

static Property* findPropertyByIndex(Property* parent, unsigned char index) {
	if (parent != NULL) {
		return parent->getChild(index);
	} else {
		return NULL;
	}
}

static Property* findPropertyByName(Property* parent, const char* name) {
	if (parent != NULL) {
		// Parse each child until one has correct name
		int index;
		for(index = 0;; index++) {
			Property* prop = parent->getChild(index);
			if (prop == NULL) {
				// no more children, abort
				return NULL;
			}
			if (!strcmp(prop->getName(), name)) {
				// match found
				return prop;
			}
		}
	} else {
		return NULL;
	}
}

static Property* findProperty(Property* parent, const char* name) {
	if (strlen(name) > 0) {
		char* endptr = NULL;
		int index = strtol(name, &endptr, 0);
		if (*endptr == 0) {
			return findPropertyByIndex(parent, index);
		} else {
			return findPropertyByName(parent, name);
		}
	} else {
		return NULL;
	}
}

static Property* findPropertyRecursive(Property* root, const char* address) {
	char buffer[1024];
	strcpy(buffer, address);
	char* ptr = buffer;
	Property *prop = root;
	for(;;) {
		char* separator = strchr(ptr, '/');
		if (separator == ptr) {
			// ignore this separator
			ptr++;
		} else if (separator != NULL) {
			// a separator has been found
			*separator = 0;
			prop = findProperty(prop, ptr);
			ptr = separator + 1;
		} else {
			// No more separator, last pass
			if (*ptr) {
				prop = findProperty(prop, ptr);
			}
			return prop;
		}
	}
}

void get_property(Property* prop) {
	PROPERTY_TYPE type = prop->getType();
	PROPERTY_VALUE value;
	prop->getValue(value);
	printf("%s\n", value_to_string(type, value));
}

void set_property(Property* prop, const char* str) {
	prop->setValue(string_to_value(prop->getType(), str));
}

int main(int argc, char* argv[]) {

	PropertyAddress rootAddress;

	// Communication stack, from lower to upper layers:
	LinuxSerialPort 		port("/dev/ttyUSB0");
	Packet 					packet(&port);
	PropertyPacket 			bridge(&packet);
	LinuxRemoteProperty		root(&rootAddress, &bridge);

	if (argc < 3) {
		usage();
		return 1;
	}
	char* command = argv[1];
	char* address = argv[2];

	Property* prop = findPropertyRecursive(&root, address);
	if (prop != NULL) {
		if (!strcmp(command, "print")) {
			// Print properties tree
			print_property(prop, 0);
		} else if (!strcmp(command, "get")) {
			// Get property value
			get_property(prop);
		} else if (!strcmp(command, "set")) {
			if (argc < 4) {
				usage();
				return 1;
			}
			char* value = argv[3];
			set_property(prop, value);
		}
	} else {
		printf("%s not found.\n", address);
		return 1;
	}

	return 0;
}
