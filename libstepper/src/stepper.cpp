/*
 * Copyright 2010-2013 Cedric Priscal
 *
 * This file is part of Octopus SDK.
 *
 * Octopus SDK is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * Octopus SDK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "octopus/stepper.h"
#include "octopus/lock.h"
#include "octopus/avr_timer.h"

#include <avr/pgmspace.h>

#define NB_ELEM(A) (sizeof(A)/sizeof(A[0]))

namespace octopus {

const uint16_t Stepper::DEFAULT_SPEED_LOOKUP_TABLE[] PROGMEM = {
    44955, 34822, 29430, 25955, 23477, 21596, 20104, 18885,
    17863, 16991, 16236, 15573, 14985, 14459, 13985, 13554,
    13161, 12801, 12468, 12160, 11874, 11607, 11357, 11123,
    10903, 10695, 10499, 10313, 10137,  9969,  9810,  9658,
    9512,  9373,  9240,  9113,  8991,  8873,  8760,  8651,
    8546,  8445,  8348,  8253,  8162,  8074,  7988,  7906,
    7825,  7747,  7672,  7598,  7527,  7458,  7390,  7324,
    7261,  7198,  7137,  7078,  7020,  6964,  6909,  6855,
    6803,  6751,  6701,  6652,  6604,  6557,  6511,  6466,
    6422,  6378,  6336,  6295,  6254,  6214,  6175,  6136,
    6098,  6061,  6025,  5989,  5954,  5920,  5886,  5852,
    5819,  5787,  5755,  5724,  5694,  5663,  5634,  5604,
    5576,  5547,  5519,  5492,  5465,  5438,  5412,  5386,
    5360,  5335,  5310,  5285,  5261,  5237,  5214,  5191,
    5168,  5145,  5123,  5101,  5079,  5057,  5036,  5015,
    4995,  4974,  4954,  4934,  4914,  4895,  4876,  4857,
    4838,  4819,  4801,  4783,  4765,  4747,  4729,  4712,
    4695,  4678,  4661,  4645,  4628,  4612,  4596,  4580,
    4564,  4548,  4533,  4518,  4503,  4488,  4473,  4458,
    4444,  4429,  4415,  4401,  4387,  4373,  4359,  4346,
    4332,  4319,  4305,  4292,  4279,  4267,  4254,  4241,
    4229,  4216,  4204,  4192,  4180,  4168,  4156,  4144,
    4132,  4121,  4109,  4098,  4086,  4075,  4064,  4053,
    4042,  4031,  4020,  4010,  3999,  3989,  3978,  3968,
    3958,  3947,  3937,  3927,  3917,  3907,  3898,  3888,
    3878,  3869,  3859,  3850,  3840,  3831,  3822,  3813,
    3803,  3794,  3785,  3777,  3768,  3759,  3750,  3741,
    3733,  3724,  3716,  3707,  3699,  3691,  3682,  3674,
    3666,  3658,  3650,  3642,  3634,  3626,  3618,  3610,
    3603,  3595,  3587,  3580,  3572,  3565,  3557,  3550,
    3543,  3535,  3528,  3521,  3514,  3506,  3499,  3492,
    3485,  3478,  3471,  3464,  3458,  3451,  3444,  3437,
    3431,  3424,  3417,  3411,  3404,  3398,  3391,  3385,
    3379,  3372,  3366,  3360,  3353,  3347,  3341,  3335
};

const Stepper::speed_t Stepper::DEFAULT_MAX_SPEED = NB_ELEM(DEFAULT_SPEED_LOOKUP_TABLE) - 1;

Stepper::Stepper(const uint16_t *speed_lookup_table,
        speed_t max_speed) :
    speed_table(speed_lookup_table),
    max_speed(max_speed),
    state(STATE_FREE_RUN),
    current_pos(0),
    target_pos(0),
    current_speed(0),
    target_speed(0),
    callback(0)
{
}

void Stepper::reachPosition(pos_t position, AsyncOperation *callback)
{
    Lock l;
    target_pos = position;
    this->callback = callback;
    state = STATE_TARGET_POS;
    run(AvrTimer::instance.now());
}

void Stepper::reachSpeed(speed_t speed, AsyncOperation *callback)
{
    Lock l;
    if (speed > max_speed) {
        target_speed = max_speed;
    } else if (speed < -max_speed) {
        target_speed = -max_speed;
    } else {
        target_speed = speed;
    }
    this->callback = callback;
    state = STATE_TARGET_SPEED;
    run(AvrTimer::instance.now());
}

void Stepper::run(Timer::time_us_t when, char what)
{
    /* Update location according to current speed */
    if (current_speed > 0) {
        current_pos++;
    } else if (current_speed < 0) {
        current_pos--;
    }

    /* Update motor rotation angle */
    step();

    /* Compute new speed */
    if (state == STATE_TARGET_SPEED) {
        if (current_speed < target_speed) {
            current_speed++;
        } else if (current_speed > target_speed) {
            current_speed--;
        } else {
            // Target speed has been reached
            state = STATE_FREE_RUN;
            // notify user
            if (callback) {
                callback->post();
            }
        }
    } else if (state == STATE_TARGET_POS) {
        // 'stop_pos' represents the position we would reach if we would try to decelerate now.
        pos_t stop_pos = current_pos - current_speed;
        if (stop_pos < target_pos) {
            if (current_speed < max_speed) {
                current_speed++;
            }
        } else if (stop_pos > target_pos) {
            if (current_speed > -max_speed) {
                current_speed--;
            }
        }

        if ( (current_pos == target_pos) && (current_speed >= -1) && (current_speed <= 1) ) {
            // Target position reached
            current_speed = 0;
            state = STATE_FREE_RUN;
            if (callback) {
                callback->post();
            }
        }
    }

    if (current_speed) {
        /* Compute waiting time before next tick */
        if (current_speed >= 0) {
            when += (Timer::time_us_t)pgm_read_word(&speed_table[current_speed]);
        } else {
            when += (Timer::time_us_t)pgm_read_word(&speed_table[-current_speed]);
        }

        /* Reprogram timer */
        AvrTimer::instance.schedule(this, when, 0);
    }
}

} /* namespace octopus */
