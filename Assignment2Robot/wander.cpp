#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "wander.h"

wander::wander() : ArAction("Wander around") {
	speed = 200;
	heading = 8;
	state = forwards;
	oldTheta = 0;
	oldX = 0;
	oldY = 0;
	angle = 0;
	distance = 0;
	travelled = 0;
}

ArActionDesired * wander::fire(ArActionDesired d) {
	desiredState.reset();

	travelled = sqrt(pow(myRobot->getX() - oldX, 2) + pow(myRobot->getY() - oldY, 2));
	//printf("Travelled = %f\n", travelled);
	//printf("getX = %f\n", myRobot->getX());
	//printf("oldX = %f\n", oldX);
	//printf("getY = %f\n", myRobot->getY());
	//printf("oldY = %f\n", oldY);


	//printf("\nold = %f\n", oldTheta);
	//printf("angle = %f\n\n", angle);

	currentTheta = myRobot->getTh();
	aim = ArMath::addAngle(oldTheta, angle);

	//printf("current = %f\n", currentTheta);
	//printf("aim = %f\n", aim);


	switch (state) {
	case forwards:
		if (travelled >= distance) {
			state = turn;
		}
		break;

	case turn:
		if (currentTheta >= aim - 5 || currentTheta <= aim + 5) {
			desiredState.setDeltaHeading(heading);
		}
		else {
			oldX = myRobot->getX();
			oldY = myRobot->getY();
			oldTheta = myRobot->getTh();
			state = forwards;
			distance = rand() % 1000 + 500;
					
			angle = rand() % 140 + 20;

			if (!((int)angle % 2 == 0)) {
				angle = -angle;
				heading = -heading;
			}
			else {
				heading = heading;
			}
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

bool wander::turnComplete() {
	double current_theta = myRobot->getTh();
	double aim = ArMath::addAngle(oldTheta, angle);

	printf("current = %f\n", current_theta);
	printf("aim = %f\n", aim);
	printf("yo = %f\n", (current_theta >= aim - 5 && current_theta <= aim + 5));

	return current_theta >= aim - 5 && current_theta <= aim + 5;
}
