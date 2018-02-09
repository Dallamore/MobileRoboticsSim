#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <Aria.h>
#include "map.h"
#include <SFML/Graphics.hpp>

map::map() : ArAction("Make a map") {
	//window();
}

ArActionDesired * map::fire(ArActionDesired d) {

	desiredState.reset();

	rX = myRobot->getX();
	rY = myRobot->getY();

	std::ofstream outfile;

	outfile.open("map.csv", std::ios::app);
	outfile << rX << "," << rY << "\n";

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