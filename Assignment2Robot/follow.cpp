#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "follow.h"

follow::follow() : ArAction("Edge Following!") {
	speed = 200;
	deltaHeading = 0;

	setPoint = 500;

	first = true;

	last_out = 0;

	pGain = 0.03;
	iGain = 0.00005;
	dGain = 1.3;

	last_angle = 0;
}

// Body of action
ArActionDesired * follow::fire(ArActionDesired d) {
	if (first) {
		//saves calling this every time
		//causes access violation when done in constructor
		//myRobot probably isn't initialised by then
		radius = myRobot->getRobotRadius();
		first = false;
	}
	desiredState.reset();

	switch (state) {
	case IDLE:
		if (myRobot->checkRangeDevicesCurrentPolar(-110, 110) - radius <= 1000) {
			state = FOLLOW;
		}
		else break;
	case FOLLOW:
		double angle;
		double dist;
		dist = myRobot->checkRangeDevicesCurrentPolar(-110, 110, &angle) - radius;
		// Find error
		prevError = error;
		error = dist - setPoint;
		if (error >= 4000) {
			error = prevError;
		}
		if (error >= 500 || error <= -500) {
			state = IDLE;
			break;
		}
		ArLog::log(ArLog::Normal, "FOLLOW: following wall %.2f mm away", dist);

		// Calculate PID output
		proportional = pGain * error;

		integral = iGain * errorHistory;

		derivative = dGain * (error - prevError);

		output = derivative + proportional + integral;

		//filter out (probable) anonamlies
		if (output < -90 || output > 90) {
			std::cout << "out: " << output;
			std::cout << ", last: " << last_out << ", ";
			std::cout << "prop: " << proportional << ", ";
			std::cout << "deriv: " << derivative;
			std::cout << std::endl;
			output = last_out;
		}
		last_out = output;
		errorHistory = errorHistory + error;

		//tries to avoid turning into a corner in some cases
		if ((angle < 0 && last_angle > 0) || (angle > 0 && last_angle < 0)) {
			angle = last_angle;
		}
		/*else if {
		output = -output;
		}*/
		//determine if wall is left or right of robot
		if (angle < 0) output = -output;
		deltaHeading = output;

		desiredState.setDeltaHeading(deltaHeading);
		last_angle = angle;

		desiredState.setVel(speed);
		state = IDLE;
		break;
	default:
		break;
	}
	return &desiredState;
}