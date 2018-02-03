#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "wander.h"

wander::wander() : ArAction("Wander around") {
	speed = 200;
	heading = 8;
	state = forwards;
	oldX = 0;
	oldY = 0;
	distance = 0;
	travelled = 0;
}

ArActionDesired * wander::fire(ArActionDesired d) {
	desiredState.reset();

	travelled = sqrt(pow(myRobot->getX() - oldX, 2) + pow(myRobot->getY() - oldY, 2));
	
	currentTheta = myRobot->getTh();
	aim = oldTheta + angle;

	switch (state) {
	case forwards:
		if (travelled >= distance) {
			state = turn;
		}
		break;

	case turn:
		if (!(currentTheta >= aim - 5 && currentTheta <= aim + 5)) {
			desiredState.setDeltaHeading(heading);
		}
		else {
			oldX = myRobot->getX();
			oldY = myRobot->getY();
			oldTheta = myRobot->getTh();
			state = forwards;
			distance = rand() % 1000 + 500;
			angle = rand() % 140 + -140;

			travelled = 0;
			printf("wander: angle %.2f     distance %.2f\n", angle, distance);
		}
		break;

	default:
		break;
	}
	desiredState.setVel(speed);

	return &desiredState;
}