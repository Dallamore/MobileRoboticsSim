#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "wander.h"

wander::wander() : ArAction("Wander around") {
	speed = 400;
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

	//printf("angle = %.2f, trav = %.2f dist = %.2f\n", angle, travelled, distance);

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
		printf("currentAngle = %.2f, angle = %.2f, trav = %.2f dist = %.2f\n", currentAngle, angle, travelled, distance);

		if (!(currentAngle >= aim - 5 && currentAngle <= aim + 5)) {
			speed = 25;
			desiredState.setDeltaHeading(heading);
		}
		else {
			oldX = myRobot->getX();
			oldY = myRobot->getY();
			oldAngle = myRobot->getTh();
			state = forwards;
			distance = rand() % 1000 + 500;

			angle = rand() % 140 + -140;

			travelled = 0;

			if (angle <= 0) {
				heading = -heading;
			}

			printf("wander: angle %.2f     distance %.2f\n", angle, distance);
		}
		break;

	default:
		break;
	}
	desiredState.setVel(speed);

	return &desiredState;
}