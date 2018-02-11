#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "wander.h"

wander::wander() : ArAction("Wander around") {
	speed = 200;
	heading = 8;
	state = beginForwards;
	distance = 1;
	travelled = 0;
	angle = 0;
}

ArActionDesired * wander::fire(ArActionDesired d) {
	desiredState.reset();
	range = myRobot->checkRangeDevicesCurrentPolar(-90, 90);
	theta = myRobot->getTh();
	if (range > 1500) {
		if (travelled > distance) {
			state = beginTurn;
			travelled = 0;
			speed = 0;
			printf("ARRIVED\n");
		}
		switch (state) {
		case beginForwards:
			distance = (rand() % 1000 + 500);
			printf("Chosen distance: %f\n", distance);
			beginForwardsX = myRobot->getX();
			beginForwardsY = myRobot->getY();
			heading = 0;
			speed = 200;
			state = duringForwards;
			break;
		case duringForwards:
			travelled = sqrt(pow(myRobot->getX() - beginForwardsX, 2) + pow(myRobot->getY() - beginForwardsY, 2));
			printf("Travelled: %f\n", travelled);
			break;
		case beginTurn:
			angle = rand() % 280 + -140;
			printf("Chosen turn: %f\n", angle);
			state = duringTurn;
			break;
		case duringTurn:
			if (theta >= angle - 5 && theta <= angle + 5) {
				printf("TURN COMPLETE\n");
				state = beginForwards;
			}
			else {
				printf("Turned = %f\n", myRobot->getTh());
				desiredState.setHeading(angle);
			}
			break;
		default:
			break;
		}
	}
	desiredState.setVel(speed);
	return &desiredState;
}
