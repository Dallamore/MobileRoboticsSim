#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "avoid.h"

avoid::avoid() : ArAction("avoid dat crash boi") {
	speed = 50;
	state = idle;
	proximity = 500;
	heading = 100;
}

ArActionDesired * avoid::fire(ArActionDesired d) {
	desiredState.reset();

	switch (state) {
	case idle:

		leftSonar = myRobot->getClosestSonarRange(-60, 0);
		rightSonar = myRobot->getClosestSonarRange(0, 60);

		if (leftSonar <= rightSonar) {
			distance = leftSonar;
			leftyRighty = 1;
		}
		else {
			distance = rightSonar;
			leftyRighty = 0;
		}

		if (distance <= proximity) {
			speed = 25;
			if (leftyRighty == 0) {
				state = right;
			}
			else{
				state = left;
			}
		}
		else {
			speed = 50;
		}
		break;
	case left:
		desiredState.setDeltaHeading(heading);
		desiredState.setVel(speed);
		state = idle;

		printf("AVOID: left turn %.2f\n", heading);

		break;

	case right:
		desiredState.setDeltaHeading(-heading);
		desiredState.setVel(speed);
		state = idle;

		printf("AVOID: right turn %.2f\n", -heading);

		break;

	default:
		break;
	}
	return &desiredState;
}