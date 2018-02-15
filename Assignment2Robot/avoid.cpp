#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "avoid.h"

avoid::avoid() : ArAction("avoid dat crash boi") {
	state = idle;
	proximity = 510;
	heading = 135;
}

ArActionDesired * avoid::fire(ArActionDesired d) {
	desiredState.reset();
	distance = myRobot->checkRangeDevicesCurrentPolar(-80, 80, &objectTheta);
	theta = myRobot->getTh();
	if (distance < proximity) {
		desiredState.setVel(0);
		printf("AVOID: stopped\n");
		switch (state) {
		case idle:
			if (objectTheta > 0) {
				state = right;
				printf("AVOID: Chosen turn: right\n");
			}
			else {
				state = left;
				printf("AVOID: Chosen turn: left\n");
			}
			break;
		case right:
			if (theta >= -heading - 5 && theta <= -heading + 5) {
				printf("AVOID: TURN COMPLETE\n");
				state = idle;
			}
			else {
				printf("AVOID: Turned = %f\n", myRobot->getTh());
				desiredState.setDeltaHeading(-heading);
			}
			break;

		case left:
			if (theta >= heading - 5 && theta <= heading + 5) {
				printf("AVOID: TURN COMPLETE\n");
				state = idle;
			}
			else {
				printf("AVOID: Turned = %f\n", myRobot->getTh());
				desiredState.setDeltaHeading(heading);
			}
			break;
		default:
			break;
		}
	}
	return &desiredState;
}