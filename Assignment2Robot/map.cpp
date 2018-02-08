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

	using namespace std;

	xs.emplace_back("1");

	ofstream mapFile;
	mapFile.open("map.csv");
	//mapFile << "This is the first cell in the first column.\n";
	//mapFile << "a,b,c,\n";
	//mapFile << "c,s,v,\n";
	//mapFile << "1,2,3.456\n";
	//mapFile << "semi;colon";
	//mapFile << "\n" << rX << "," << rY << "\n";
	

	mapFile << xs.a << "\n";



	//printf("rX: %.2f xY: %.2f\n", rX, rY);
	mapFile.close();



	

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