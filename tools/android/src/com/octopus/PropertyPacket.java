/*
 * Copyright 2010,2011 Cedric Priscal
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

package com.octopus;

/**
 * @brief Class used to transmit and received messages on a serial link.
 * The incoming messages are forwarded either to a RemotePropertyServer, either to
 * a RemotePropertyClient.
 */
public class PropertyPacket implements IPacketListener {
	
	static final byte ADDRESS_NODE_MAX_VALUE = (byte) 246;
	static final byte CMD_GET_TYPE         	= (byte) 247;  // 0xf7
	static final byte RET_GET_TYPE         	= (byte) 248;  // 0xf8
	static final byte CMD_GET_NAME 			= (byte) 249;	// 0xf9
	static final byte RET_GET_NAME         	= (byte) 250;  // 0xfa
	static final byte CMD_GET_DESCRIPTION	= (byte) 251;  // 0xfb
	static final byte RET_GET_DESCRIPTION	= (byte) 252;  // 0xfc
	static final byte CMD_GET_VALUE 		= (byte) 253;  // 0xfd
	static final byte RET_GET_VALUE 		= (byte) 254;  // 0xfe
	static final byte CMD_SET_VALUE 		= (byte) 255;  // 0xff

	private Packet						mPacket;
	private IPropertyPacketListener     mServer;
	private IPropertyPacketListener     mClient;
	private boolean						mEscape;
	private byte[]						mAddress;
	private char                        mAddressSize;
	private byte						mCommand;
	private byte[]						mData;
	private char           				mDataSize;

	public PropertyPacket(Packet packet) {
		mPacket = packet;
	    mClient = null;
	    mServer = null;
		mPacket.registerListener(this);
	}

	public void registerClient(IPropertyPacketListener client) {
		mClient = client;
	}

	public void registerServer(IPropertyPacketListener server) {
		mServer = server;
	}

	@Override
	public void onPacketReceived(byte[] data) {

		PropertyAddress address = new PropertyAddress();

		for (int i = 0; i < data.length; i++) {
			if (data[i] > ADDRESS_NODE_MAX_VALUE) {
				// address is finished
				address.mData = new byte[i];
				System.arraycopy(data, 0, address.mData, 0, i);
				byte[] params = new byte[data.length - i - 1];
				System.arraycopy(data, i+1, params, 0, params.length);

				switch(data[i]) {
				case CMD_GET_TYPE:
				case CMD_GET_NAME:
				case CMD_GET_DESCRIPTION:
				case CMD_GET_VALUE:
				case CMD_SET_VALUE:
					// Packet is a request: RemotePropertyServer will deal with it.
					mServer.onPropertyPacketReceived(address, data[i], params);
					break;
				case RET_GET_TYPE:
				case RET_GET_NAME:
				case RET_GET_DESCRIPTION:
				case RET_GET_VALUE:
					// Packet is a response: RemotePropertyClient will deal with it.
					mClient.onPropertyPacketReceived(address, data[i], params);
					break;
				}
				return;
			}
		}

	}

	public void send(PropertyAddress address, byte command, final byte[] data) {
		
		byte[] packet = new byte[64];
		char i,j;
		for (i=0; i<address->mSize; i++) {
			packet[(int)i] = address->mData[(int)i];
		}
		packet[(int)i++] = command;
		for (j=0; j<size; j++) {
			packet[(int)i++] = data[(int)j];
		}
		mPacket->sendPacket(packet, i);
	}
}
