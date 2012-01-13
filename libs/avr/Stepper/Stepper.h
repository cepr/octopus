/*
 * Copyright 2010 Cedric Priscal
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

#ifndef STEPPER_H_
#define STEPPER_H_

#include "Timer/timer_listener.h"
#include "StepperListener.h"
#include "Module.h"
#include "Property.h"
#include "property_record.h"
#include "property_data.h"

class PropertyStepperTargetLocation: public PropertyS16 {
private:
    const char* getName() {return "target";}
    const char* getDescription() {return "Target location in absolute steps.";}
    PropertyListener* mListener;
    void setValue(const PROPERTY_VALUE* value) {
        if (value->s16 != mValue) {
            mValue = value->s16;
            if (mListener) {
                mListener->onPropertyChanged(this);
            }
        }
    }
public:
    PropertyStepperTargetLocation(PropertyListener* listener) : PropertyS16(), mListener(listener) {}
//    short operator= (short value) {
//    	return PropertyS16::operator=(value);
//	}
};

class PropertyStepperCurrentLocation: public PropertyS16 {
private:
    const char* getName() {return "current";}
    const char* getDescription() {return "Current location in absolute steps.";}
public:
    PropertyStepperCurrentLocation() : PropertyS16() {}
    using PropertyS16::operator =;
    using PropertyS16::operator ++;
    using PropertyS16::operator --;
};

class PropertyStepperManual: public PropertyBoolean {
private:
    const char* getName() {return "manual";}
    const char* getDescription() {return "";}
    PropertyListener* mListener;
    void setValue(const PROPERTY_VALUE* value) {
        if (value->boolean != mValue) {
            mValue = value->boolean;
            mListener->onPropertyChanged(this);
        }
    }
public:
    PropertyStepperManual(PropertyListener* listener) : PropertyBoolean(), mListener(listener) {}
//    bool operator= (bool value) {
//    	return PropertyBoolean::operator=(value);
//	}
};

/**
 * @brief Abstract base class for all step motor drivers.
 *
 * @see Stepper4B
 * @see Stepper4C
 * @see Stepper4D
 */
class Stepper : public TimerListener, public Module, public PropertyRecord, public PropertyListener {

private:
    short mCurrentSpeed;						/**< current speed in steps/(second/8) */
    StepperListener *mFinishListener;			/**< listener to be called when stepper has reached its target */
    bool mTimerStarted;
    void onTimer(char what, unsigned short when); // for TimerListener
    virtual void tick()=0;
    virtual void setEnabled(bool enable)=0;

protected:
    Stepper(char pinA1, char pinA2, char pinB1, char pinB2);
#ifdef HALF_STEP
    unsigned char PinsSequence[8];
#else
    unsigned char PinsSequence[4];
#endif
    unsigned char PinsMask;

public:

    /**
     * @brief Current stepper position, in absolute number of steps.
     */
    PropertyStepperCurrentLocation mCurrentLocation;

    /**
     * @brief Target stepper position, in absolute number of steps.
     */
	PropertyStepperTargetLocation mTargetLocation;

	/**
	 * @brief Define if mTargetLocation must be considered as absolute, or as manual control.
	 */
	PropertyStepperManual mManual;

    /**
     * @brief Register a listener to stepper events.
     *
     * You can register a listener in order to be notified when the destination has been reached.
     *
     * You can modify mTargetLocation at any moment to change the destination, even if stepper is
     * already moving, but the listener will be called only when mCurrentLocation == mTargetLocation.
     *
     * @param[in] finishListener A listener.
     *
     * @see StepperListener
     */
    void registerListener(StepperListener *finishListener);

    PROPERTY_TYPE getType();
    Property* getChild(unsigned char index);

    virtual const char* getName()=0;
    virtual const char* getDescription()=0;

    void onPropertyChanged(class Property* prop);
};

#endif /* STEPPER_H_ */