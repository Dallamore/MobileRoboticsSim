#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <Aria.h>
#include "map.h"
#include <SFML/Graphics.hpp>

map::map() : ArAction("Make a map") {
	//window();

	robotX = 12.6;
	robotY = 4.3;
	robotTh = -0.2;
	r = 1.1;
	thetaS = 1.35;

}

ArActionDesired * map::fire(ArActionDesired d) {
	desiredState.reset();

	
	if (leftSonar < 3500) {

		//robotX = myRobot->getX();
		//robotY = myRobot->getY();
		//robotTh = myRobot->getTh();
		//r = (myRobot->checkRangeDevicesCurrentPolar(90, -90, &angle));
		////hypot = sqrt(pow(robotX, 2) + pow(robotY, 2));
		//thetaS = ArMath::sin(robotY / r);

		//Step One - find x and y
		x = ArMath::cos(thetaS) * (r);
		y = ArMath::sin(thetaS) * (r);

		//Step Two - rotate to global coordinates
		ArMath::pointRotate(&x, &y, robotTh);

		//Step Three - translate to global coordinates
		xs = robotX + x;
		ys = robotY + y;

		std::ofstream outfile;
		outfile.open("map.csv", std::ios::app);
		outfile << xs << "," << ys << "\n";

		std::cout << xs << "," << ys << "\n";

		
	}

	


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