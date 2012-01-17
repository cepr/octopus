/*
 * Copyright 2011 Cedric Priscal
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

#include "Robot/Robot.h"
#include "property_record.h"
#include "AvrUsart/AvrUsart.h"
#include "UsartListener.h"
#include "Packet.h"
#include "Blink/Blink.h"
#include "PropertyPacket.h"
#include "RemotePropertyServer.h"

/**
 * @brief RC Car with one DC motor for throttle and one coil for direction
 *
 * Both channels are PWM controlled using AVR Timer0 in Fast PWM mode.
 *
 * \par Pinout
 * <TABLE>
 * <TR><TH> Arduino pin </TH><TH> ATMEGA328P pin </TH><TH> Motor driver pin (TB6612FNG) </TH></TR>
 * <TR><TD> 2           </TD><TD> PD2            </TD><TD> AIN2							</TD></TR>
 * <TR><TD> 3           </TD><TD> PD3            </TD><TD> AIN1							</TD></TR>
 * <TR><TD> 4           </TD><TD> PD4            </TD><TD> BIN1							</TD></TR>
 * <TR><TD> 5           </TD><TD> OC0B           </TD><TD> PWMB							</TD></TR>
 * <TR><TD> 6           </TD><TD> OC0A           </TD><TD> PWMA							</TD></TR>
 * <TR><TD> 7           </TD><TD> PD7            </TD><TD> BIN2							</TD></TR>
 * <TR><TD> 8           </TD><TD> PB0            </TD><TD> STBY							</TD></TR>
 * </TABLE>
 */
class TwoChannelsCar : public Robot, public PropertyRecord {

private:
    // List of modules
    Blink 					mBlink;

	class Throttle : public PropertyS8 {
	private:
		const char* getName() const  { return "Throttle"; }
		const char* getDescription() { return "Throttle"; }
        void setValue(const PROPERTY_VALUE & value) {
            operator=(value.s8);
        }
	public:
		signed char operator=(signed char value) {
			mValue = value;
			if (value > 0) {
				// go forward
				OCR0A = ((unsigned char)value) << 1;
				PORTD = (PORTD & (~_BV(PD2))) | _BV(PD3);
			} else if (value < 0) {
				// go backward
				if (value > -128)
					OCR0A = ((unsigned char)(-value)) << 1;
				else
					OCR0A = 0xff;
				PORTD = (PORTD & (~_BV(PD3))) | _BV(PD2);
			} else {
				// stop engine
				OCR0A = 0;
				PORTD = PORTD & (~(_BV(PD2) | _BV(PD3)));
			}
			return value;
		}
	};

	class Direction : public PropertyS8 {
	private:
		const char* getName() const { return "Direction"; }
		const char* getDescription() { return "Direction"; }
        void setValue(const PROPERTY_VALUE & value) {
            operator=(value.s8);
        }
	public:
		signed char operator=(signed char value) {
			mValue = value;
			if (value > 0) {
				// go right
				OCR0B = value;
				PORTD = (PORTD & (~_BV(PD7))) | _BV(PD4);
			} else if (value < 0) {
				// go left
				OCR0B = -value;
				PORTD = (PORTD & (~_BV(PD4))) | _BV(PD7);
			} else {
				// stop engine
				OCR0B = 0;
				PORTD = PORTD & (~(_BV(PD4) | _BV(PD7)));
			}
			return value;
		}
	};

	Throttle				mThrottle;
	Direction				mDirection;

    // Remote control
	AvrUsart 				mAvrUsart;
	Packet 					mPacket;
	PropertyPacket 			mBridge;
	RemotePropertyServer 	mServer;

public:
    // Constructor
    TwoChannelsCar() : PropertyRecord(),
                 // Modules
                 mBlink(),
                 // Remote control
                 mAvrUsart(AvrUsart::B57600),
                 mPacket(&mAvrUsart),
                 mBridge(&mPacket),
                 mServer(this, &mBridge)
    {
        mBridge.registerServer(&mServer);
		// Set pins to zero
		PORTD &= ~(_BV(DDD2) | _BV(DDD3) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7));
		PORTB &= ~_BV(PB0);
		// Set pins in output
		DDRD |= _BV(DDD2) | _BV(DDD3) | _BV(DDD4) | _BV(DDD5) | _BV(DDD6) | _BV(DDD7);
		DDRB |= _BV(DDB0);
		// Configure OC0A and OC0B pins
		TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00);
		// Set prescaler to 1:1
		TCCR0B = _BV(CS00);

		// Set 
		mThrottle = 0;
		mDirection = 0;

		// Activate STBY
		PORTB |= _BV(PB0);
    }

    // Property definition
	const char* getName() const {
        return "TwoChannelsCar";
    }

	const char* getDescription() {
        return "TwoChannelsCar robot";
    }

    void onStart() {
        mBlink.mEnabled = true;
		mAvrUsart.sendString("Hello !\n");
		//for (;;)
			//mAvrUsart.sendByte(0xAA);
    }

    Property* getChild(unsigned char index) {
       	switch(index) {
            case 0: return &mBlink;
			case 1: return &mThrottle;
			case 2: return &mDirection;
            default: return 0;
        }
    }
};

static TwoChannelsCar gTwoChannelsCar;

int main(void)
{
	gTwoChannelsCar.onStart();
	Event::startLooper();
	return 0;
}
