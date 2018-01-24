#include <iostream>
#include <stdlib.h>
#include <Aria.h>

#include "follow.h"
// Implementation

// Constructor
follow::follow() : ArAction("Follow Edge")
{
  speed = 50; // Set the robots speed to 50 mm/s. 200 is top speed
  deltaHeading = 0; // Straight line

  setPoint = 500; // 0.5 m

  // Proportional control
  pGain = 0; // CHANGE THIS
}

// Body of action
ArActionDesired * follow::fire(ArActionDesired d)
{
 desiredState.reset(); // reset the desired state (must be done)

 // Get sonar readings
 leftSonar = myRobot->getClosestSonarRange(-20, 100);
 rightSonar = myRobot->getClosestSonarRange(-100, 20);

 // Find error
 error = 0; // CHANGE THIS

 // Calculate proportional output
 output = 0; // CHANGE THIS

 // Implement control action
 deltaHeading = output; 

 std::cout << leftSonar << " " << rightSonar << " " << error << " " << output << std::endl;

 desiredState.setVel(speed); // set the speed of the robot in the desired state
 desiredState.setDeltaHeading(deltaHeading); // Set the heading change of the robot

 return &desiredState; // give the desired state to the robot for actioning
}


