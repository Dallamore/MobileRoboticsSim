#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "wander.h"

wander::wander() : ArAction("Wander around") {
	speed = 200;
	heading = 8;
	state = forwards;
	oldTheta =
		oldX =
		oldY =
		angle =
		distance =
		travelled = 0;
}

ArActionDesired * wander::fire(ArActionDesired d) {
	desiredState.reset();

	travelled = sqrt(pow(myRobot->getX() - oldX, 2) + pow(myRobot->getY() - oldY, 2));

	switch (state) {
	case forwards:
		if (travelled >= distance) {
			state = turn;
		}
		break;
	case turn:
		if (!turnComplete()) {
			desiredState.setDeltaHeading(heading);
		}
		else {
			oldX = myRobot->getX();
			oldY = myRobot->getY();
			oldTheta = myRobot->getTh();
			state = forwards;
			distance = (rand() % 1000) + 500; //get pseudo-random num between 500 & 1500
			angle = (rand() % 140) + 20; //get pseudo-random num between 20 & 160

			if ((bool)((int)angle % 2)) { //if angle is odd turn right
				angle = -angle;
				heading = -fabs(heading);
			}
			else {
				heading = fabs(heading);
			}
			travelled = 0;
			ArLog::log(ArLog::Normal, "WANDER: turning %.2f degrees after %.2f mm", angle, distance);
		}
		break;
	default:
		break;
	}
	desiredState.setVel(speed);

	return &desiredState;
}

bool wander::turnComplete() {
	double current_theta = myRobot->getTh();
	double aim = ArMath::addAngle(oldTheta, angle);

	return current_theta >= aim - 5 && current_theta <= aim + 5;
}
