#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <Aria.h>
#include "map.h"
#include <SFML/Graphics.hpp>

map::map() : ArAction("Make a map") {

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
	angle = myRobot->getTh();

	//sonarNum = myRobot->getClosestSonarNumber(90, -90);

	//r = myRobot->getSonarRange(sonarNum);

	r = (myRobot->checkRangeDevicesCurrentPolar(90, -90, &angle));

	if (r <= 3500 && count % 2 == 0) {
		if (count >= 10) {
			count = 0;
		}

		robotX = myRobot->getX();
		robotY = myRobot->getY();
		robotTh = myRobot->getTh();

		thetaS = sin(robotY / r);
		//radius = myRobot->getRobotRadius();
		radius = 0.6;

		//Step One - find x and y
		x = cos(thetaS) * (r + radius);
		y = sin(thetaS) * (r + radius);

		//Step Two - rotate to global coordinates

		//x = ArMath::radToDeg(x);
		//y = ArMath::radToDeg(y);

		ArMath::pointRotate(&x, &y, robotTh);

		//Step Three - translate to global coordinates
		xs = robotX + x;
		ys = robotY + y;

		printf("xs = %f, ys = %f\n", xs, ys);

		//Print to CSV
		std::ofstream outfile;
		outfile.open("map.csv", std::ios::app);
		outfile << xs << "," << ys << "\n";

	}
	
	count++;
	
	return &desiredState;
}














int map::window()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}