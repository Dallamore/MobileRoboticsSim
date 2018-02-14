#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "avoid.h"

avoid::avoid() : ArAction("avoid dat crash boi") {
	state = idle;
	proximity = 500;
	heading = 135;
	state = idle;
}

ArActionDesired * avoid::fire(ArActionDesired d) {
	desiredState.reset();
	distance = myRobot->checkRangeDevicesCurrentPolar(-100, 100, &objectTheta);
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



//theta = myRobot->getTh();
//switch (state) {
//case idle:
//	if (distance < proximity) {
//		state = turn;
//		speed = 0;
//	}
//	else
//	{
//		speed = 200;
//	}
//	break;
//case turn:
//	if (theta >= heading - 5 && theta <= heading + 5) {
//		printf("AVOID: TURN COMPLETE\n");
//		state = idle;
//	}
//	else {
//		printf("AVOID: Turned = %f\n", myRobot->getTh());
//		desiredState.setDeltaHeading(heading);
//	}
//	break;
//default:
//	break;
//}
//
//desiredState.setVel(speed);
//return &desiredState;
//}






//distance = myRobot->checkRangeDevicesCurrentPolar(-60, 60);
//
//switch (state) {
//case idle:
//	leftSonar = myRobot->getClosestSonarRange(-60, 0);
//	rightSonar = myRobot->getClosestSonarRange(1, 60);
//	if (leftSonar <= rightSonar) {
//		distance = leftSonar;
//		leftOrRight = 1;
//	}
//	else {
//		distance = rightSonar;
//		leftOrRight = 0;
//	}
//
//	if (distance <= proximity) {
//		if (leftOrRight == 0) {
//			state = right;
//		}
//		else {
//			state = left;
//		}
//	}
//	break;
//case left:
//	desiredState.setDeltaHeading(heading);
//	state = idle;
//	printf("AVOID: left turn %.2f\n", heading);
//	break;
//case right:
//	desiredState.setDeltaHeading(-heading);
//	state = idle;
//	printf("AVOID: right turn %.2f\n", -heading);
//	break;
//default:
//	break;
//}
//return &desiredState;
//}