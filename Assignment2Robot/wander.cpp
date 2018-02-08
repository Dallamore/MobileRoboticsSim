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

	currentAngle = myRobot->getTh();
	aim = oldAngle + angle;

	if (travelled >= distance) {
		state = turn;
		travelled = 0;
	}
	else {
		state = forwards;
	}

	switch (state) {
	case forwards:
		speed = 200;
		break;
	case turn:
		//printf("currentAngle = %.2f, angle = %.2f\n", currentAngle, angle);

		if (currentAngle >= aim - 5 && currentAngle <= aim + 5) {
			oldX = myRobot->getX();
			oldY = myRobot->getY();
			oldAngle = myRobot->getTh();
			state = forwards;
			distance = (rand() % 1000 + 500);

			/*int min = -90;
			int max = 180;
			angle = (min + (rand() % (int)(max - min)));*/


			angle = rand() % 280 + -140;

			heading = angle;

			travelled = 0;

			if (angle <= currentAngle) {
				heading = -heading;
			}


			printf("wander: angle %.2f     distance %.2f\n", angle, distance);
		}
		else {
			speed = 50;
			desiredState.setDeltaHeading(heading);
		}
		break;

	default:
		break;
	}
	desiredState.setVel(speed);

	return &desiredState;
}