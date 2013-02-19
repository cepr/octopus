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
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Octopus SDK.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void usage() {
	printf(
        "step_table <wheel diameter> <steps> <max speed> <acceleration duration>\n"
		"\n"
		" wheel diameter        : Wheel diameter in centimeters.\n"
		" steps                 : Number of steps for one rotation.\n"
		" max speed             : Maximum speed in meters/second.\n"
		" acceleration duration : Time to reach the maximum speed, in seconds.\n"
	);
}

int main(int argc, char *argv[]) {

	if (argc != 5) {
		usage();
		return 1;
	}

	double wheel_diameter_m        = atof(argv[1]);
	double steps_                  = atof(argv[2]);
	double max_speed_mps           = atof(argv[3]);
	double acceleration_duration_s = atof(argv[4]);

	printf(
			"/* This file has been generated using the command:\n"
            " * > step_table %f %f %f %f\n"
			" */\n"
			"\n"
			"#ifndef ACCELERATIONTABLE_H_\n"
			"#define ACCELERATIONTABLE_H_\n"
            "\n"
            "#include <avr/pgmspace.h>\n"
			"\n"
            "static const unsigned short DELAYS[] PROGMEM = {\n",
			wheel_diameter_m, steps_, max_speed_mps, acceleration_duration_s
	);

	double acceleration_mpss = max_speed_mps / acceleration_duration_s;
	double distance_m = 0.5 * acceleration_mpss * acceleration_duration_s * acceleration_duration_s;
	double distance_per_step_m = wheel_diameter_m * 3.1415927 / 400;
	double distance_ = distance_m / distance_per_step_m;

	int c = 0;
	double x_;
	double x_m;
	double T_s;
	double T_us;

	for (x_ = 0; x_ < distance_-1; x_++) {
		x_m = (x_+0.5) * distance_per_step_m;
		T_s = 1 / sqrt(2*acceleration_mpss*x_m);
		T_us = T_s * 1000.;
		if (T_us < 65536) {
			c++;
			if (c < 8) {
				printf("%5d, ", (int)T_us);
			} else {
				printf("%5d,\n", (int)T_us);
				c = 0;
			}
		}
	}
	x_m = (x_+0.5) * distance_per_step_m;
	T_s = 1 / sqrt(2*acceleration_mpss*x_m);
	T_us = T_s * 1000.;
	if (T_us < 65536) {
		printf("%5d\n", (int)T_us);
	}

	printf(
			"};\n"
			"\n"
			"#endif /* ACCELERATIONTABLE_H_ */\n"
	);
}
