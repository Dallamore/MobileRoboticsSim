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

	//sonarNum = myRobot->getClosestSonarNumber(-90, 90);
	//r = myRobot->getSonarRange(sonarNum);

	r = (myRobot->checkRangeDevicesCurrentPolar(-90, 90));

	if (r <= 3500 && count >= 10) {
		count = 0;

		robotX = myRobot->getX();
		robotY = myRobot->getY();
		robotTh = myRobot->getTh();

		thetaS = sin(robotY / r);
		radius = myRobot->getRobotRadius();
		//radius = 0.6;

		//Step One - find x and y
		x = cos(thetaS) * (r + radius);
		y = sin(thetaS) * (r + radius);

		//Step Two - rotate to global coordinates

		ArMath::pointRotate(&x, &y, robotTh);

		//Step Three - translate to global coordinates
		xs = robotX + x;
		ys = robotY + y;

		//printf("xs = %f, ys = %f\n", xs, ys);

		//Print to CSV file
		std::ofstream outfile;
		outfile.open("map.csv", std::ios::app);
		outfile << xs << "," << ys << "\n";

	}
	
	count++;
	
	return &desiredState;
}