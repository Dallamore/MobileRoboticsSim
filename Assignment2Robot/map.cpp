#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <Aria.h>
#include "map.h"

map::map() : ArAction("Cartographer all up in here") {
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

	//something wrong with the sonar

	//sonarNum = myRobot->getClosestSonarNumber(95, 85);
	//r = myRobot->getSonarRange(1);

	//printf("R: %f\n", r);

	r = (myRobot->checkRangeDevicesCurrentPolar(40, 60, &objectTheta));

	if (r <= 3500 && count >= 5) {
		count = 0;

		robotX = myRobot->getX();
		robotY = myRobot->getY();
		robotTh = -myRobot->getTh();

		//objectTheta = sin(robotY / r);
		radius = myRobot->getRobotRadius();
		//radius = 0.6;

		//Step One - find x and y
		//objectX = cos(objectTheta) * (r + radius);
		//objectY = sin(objectTheta) * (r + radius);
		objectX = ArMath::cos(objectTheta) * (r + radius);
		objectY = ArMath::sin(objectTheta) * (r + radius);

		//Step Two - rotate to global coordinates

		ArMath::pointRotate(&objectX, &objectY, robotTh);

		//Step Three - translate to global coordinates
		xs = robotX + objectX;
		ys = robotY + objectY;

		printf("xs = %f, ys = %f\n", xs, ys);

		//Print to CSV file
		std::ofstream outfile;
		outfile.open("map.csv", std::ios::app);
		outfile << xs << "," << ys << "\n";

	}
	
	count++;
	
	return &desiredState;
}