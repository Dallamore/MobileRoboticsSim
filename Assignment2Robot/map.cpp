#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <Aria.h>
#include "map.h"

map::map() : ArAction("Cartographer all up in here") {
	//Know values for testing, answers should be 13.3, 5.85
	//robotX = 12.6;
	//robotY = 4.3;
	//robotTh = -0.2;
	//r = 1.1;
	//thetaS = 1.35;
	//radius = 0.6;

	count = 0;
}

ArActionDesired * map::fire(ArActionDesired d) {
	//C++ cos/sin uses radians
	//ArMath cos/sin uses degrees

	desiredState.reset();
	r = (myRobot->checkRangeDevicesCurrentPolar(-90, 90, &objectTheta));
	if (r <= 3500 && count >= 5) {
		count = 0;

		robotX = myRobot->getX();
		robotY = myRobot->getY();
		robotTh = myRobot->getTh();

		radius = myRobot->getRobotRadius();

		//Step One - find x and y
		objectX = ArMath::cos(objectTheta) * (r + radius);
		objectY = ArMath::sin(objectTheta) * (r + radius);

		//Step Two - rotate to global coordinates
		ArMath::pointRotate(&objectX, &objectY, robotTh);

		//Step Three - translate to global coordinates
		xs = robotX + objectX;
		ys = robotY + objectY;

		//Print to CSV file
		output.open("map.csv", std::ios::app);
		output << xs << "," << ys << "\n";
	}
	count++;
	return &desiredState;
}