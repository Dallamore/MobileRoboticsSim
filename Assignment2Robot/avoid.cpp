#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "avoid.h"

avoid::avoid() : ArAction("avoid dat crash boi") {
	state = idle;
	proximity = 500;
	heading = 90;
	state = idle;
}

ArActionDesired * avoid::fire(ArActionDesired d) {
	desiredState.reset();
	distance = myRobot->checkRangeDevicesCurrentPolar(-60, 60);
	theta = myRobot->getTh();
	switch (state) {
	case idle:
		if (distance <= proximity) {
			state = turn;
			speed = 0;
		}
		else
		{
			speed = 200;
		}
		break;
	case turn:
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
	
	desiredState.setVel(speed);
	return &desiredState;
}

















//	switch (state) {
//	case idle:
//		leftSonar = myRobot->getClosestSonarRange(-60, 0);
//		rightSonar = myRobot->getClosestSonarRange(1, 60);
//		if (leftSonar <= rightSonar) {
//			distance = leftSonar;
//			leftOrRight = 1;
//		}
//		else {
//			distance = rightSonar;
//			leftOrRight = 0;
//		}
//
//		if (distance <= proximity) {
//			if (leftOrRight == 0) {
//				state = right;
//			}
//			else{
//				state = left;
//			}
//		}
//		else {
//		}
//		break;
//	case left:
//		desiredState.setDeltaHeading(heading);
//		state = idle;
//		printf("AVOID: left turn %.2f\n", heading);
//		break;
//	case right:
//		desiredState.setDeltaHeading(-heading);
//		state = idle;
//		printf("AVOID: right turn %.2f\n", -heading);
//		break;
//	default:
//		break;
//	}
//	return &desiredState;
//}