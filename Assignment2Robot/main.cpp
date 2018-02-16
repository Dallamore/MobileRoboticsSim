#include "Aria.h"
#include "follow.h"
#include "wander.h"
#include "avoid.h"
#include "map.h"
#include <SFML/Graphics.hpp>

int main(int argc, char **argv)
{
  Aria::init();
  ArArgumentParser argParser(&argc, argv);
  argParser.loadDefaultArguments();
  ArRobot robot;
  ArRobotConnector robotConnector(&argParser, &robot);
  ArLaserConnector laserConnector(&argParser, &robot, &robotConnector);

  // Always try to connect to the first laser:
  argParser.addDefaultArgument("-connectLaser");

  if(!robotConnector.connectRobot())
  {
    ArLog::log(ArLog::Terse, "Could not connect to the robot.");
    if(argParser.checkHelpAndWarnUnparsed())
    {
        // -help not given, just exit.
        Aria::logOptions();
        Aria::exit(1);
    }
  }

  // Trigger argument parsing
  if (!Aria::parseArgs() || !argParser.checkHelpAndWarnUnparsed())
  {
    Aria::logOptions();
    Aria::exit(1);
  }

  ArKeyHandler keyHandler;
  Aria::setKeyHandler(&keyHandler);
  robot.attachKeyHandler(&keyHandler);

  puts("Press  Escape to exit.");
  
  ArSonarDevice sonar;
  robot.addRangeDevice(&sonar);

  robot.runAsync(true);
  
  // try to connect to laser. if fail, warn but continue, using sonar only
  if(!laserConnector.connectLasers())
  {
    ArLog::log(ArLog::Normal, "Warning: unable to connect to requested lasers, will wander using robot sonar only.");
  }

  // turn on the motors
  robot.enableMotors();

  // add a set of actions that combine together to effect the wander behavior
  ArActionStallRecover recover;
  ArActionBumpers bumpers;
  edgeFollow follow;
  wander wander;
  avoid avoid;
  map map;

  robot.addAction(&recover, 100);
  robot.addAction(&bumpers, 75);
  robot.addAction(&avoid, 70);
  robot.addAction(&follow, 60);
  robot.addAction(&wander, 50);
  robot.addAction(&map, 40);

  //sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
  //sf::CircleShape shape(1);
  //shape.setFillColor(sf::Color::Green);
  //shape.setPosition(200, 400);
  ////double x = map.xs;
  //while (window.isOpen())
  //{
	 // sf::Event event;
	 // while (window.pollEvent(event))
	 // {
		//  if (event.type == sf::Event::Closed)
		//	  window.close();
	 // }
	 // window.clear();
	 // window.draw(shape);
	 // window.display();
  //}

  // wait for robot task loop to end before exiting the program
  robot.waitForRunExit();
  
  Aria::exit(0);
}
