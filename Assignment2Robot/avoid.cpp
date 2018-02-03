#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "avoid.h"

avoid::avoid() : ArAction("Edge Following!") {
	speed = 50;
	limit = 150;
	state = idle;
	proximity = 250;
	heading = 135;

}

ArActionDesired * avoid::fire(ArActionDesired d) {
	desiredState.reset();

	double dist;

	switch (state) {
	case idle:
		dist = myRobot->checkRangeDevicesCurrentPolar(-60, 60, &angle) - myRobot->getRobotRadius();
		if (dist <= proximity) {
			speed = 25;
			if (angle > 0) {
				state = right;
			}
			else {
				state = left;
			}
		}
		else {
			speed = 50;
		}
		break;
	case left:
		ArLog::log(ArLog::Normal, "AVOID turning %.2f", heading);
		desiredState.setDeltaHeading(heading);
		desiredState.setVel(speed);
		state = idle;
		break;

	case right:
		ArLog::log(ArLog::Normal, "AVOID turning %.2f", -heading);
		desiredState.setDeltaHeading(-heading);
		desiredState.setVel(speed);
		state = idle;
		break;
	default:
		break;
	}
	return &desiredState;
}