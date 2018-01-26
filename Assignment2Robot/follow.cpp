#include <iostream>
#include <stdlib.h>
#include <Aria.h>
#include "follow.h"

follow::follow() : ArAction("Edge Following!") {
	speed = 200;
	deltaHeading = 0;

	setPoint = 500;

	first = true;

	last_out = 0;

	pGain = 0.03;		//0.03
	iGain = 0.00005;	//0.00005
	dGain = 1.3;		//1.3

	last_angle = 0;
}

ArActionDesired * follow::fire(ArActionDesired d) {
	if (first) {
		radius = myRobot->getRobotRadius();
		first = false;
	}
	desiredState.reset();

	double distance;

	leftSonar = myRobot->getClosestSonarRange(-10, 100);
	rightSonar = myRobot->getClosestSonarRange(-100, 10);

	if (leftSonar <= rightSonar) {
		distance = leftSonar;
	}
	else {
		distance = rightSonar;
	}

	switch (state) {
	case IDLE:
		if (distance <= 1000) {
			state = FOLLOW;
		}
		else {
			break;
		}

	case FOLLOW:
		
		prevError = error;
		error = distance - setPoint;

		if (error >= 4000) {
			error = prevError;
		}
		if (error >= 500 || error <= -500) {
			state = IDLE;
			break;
		}
		
		printf("edgeFollow: %.2f\n", distance);

		pOut = pGain * error;
		iOut = iGain * errorHistory;
		dOut = dGain * (error - prevError);

		output = dOut + pOut + iOut;

		last_out = output;
		errorHistory = errorHistory + error;

		if (angle < 0) output = -output;
		deltaHeading = output;

		desiredState.setDeltaHeading(deltaHeading);
		last_angle = angle;

		desiredState.setVel(speed);

		state = IDLE;
		
		break;

	default:
		break;
	}
	return &desiredState;
}