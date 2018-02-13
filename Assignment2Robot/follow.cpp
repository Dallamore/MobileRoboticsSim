#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "follow.h"

edgeFollow::edgeFollow() : ArAction("Stickin' to the straight and narrow") {
	speed = 200;
	setPoint = 1000;
	pGain = 0.03;		//0.03
	iGain = 0.00005;	//0.00005
	dGain = 1.3;		//1.3
}

ArActionDesired * edgeFollow::fire(ArActionDesired d) {
	desiredState.reset();
	leftSonar = myRobot->getClosestSonarRange(-10, 100);
	rightSonar = myRobot->getClosestSonarRange(-100, 10);

	if (leftSonar <= rightSonar) {
		distance = leftSonar;
		leftOrRight = 0;
	}
	else {
		distance = rightSonar;
		leftOrRight = 1;
	}

	switch (state) {
	case idle:
		if (distance <= 1500) {
			state = following;
		}
		else {
			break;
		}
	case following:
		prevError = error;
		error = distance - setPoint;
		if (error >= 4000) {
			error = prevError;
		}
		if (error > 500 || error <= -500) {
			state = idle;
			break;
		}
		printf("FOLLOW: %.2f\n", distance);
		pOut = pGain * error;
		iOut = iGain * errorHistory;
		dOut = dGain * (error - prevError);
		output = dOut + pOut + iOut;
		errorHistory = errorHistory + error;

		//if (leftOrRight == 1){
		//	output = -output;
		//}

		desiredState.setDeltaHeading(output);
		desiredState.setVel(speed);
		state = idle;
		break;
	default:
		break;
	}
	return &desiredState;
}