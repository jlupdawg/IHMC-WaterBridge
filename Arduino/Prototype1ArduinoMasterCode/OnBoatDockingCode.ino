/***********SONAR*******************************************************************************************/
float sonarDist1; //holds the distances sensed by the dock sonars
float sonarDist2;
float dockingValue = 20; //the closest distance we want to get to the sonars before stopping

/***********HEADING*****************************************************************************************/
float headingError; //Potentially get rid of this if using incrementing method
float desiredHeading;
float currentHeading;

/***********DOCKING****************************************************************************************/
boolean verifiedBoat = true; //stores whether the boat has confirmed that it is the object returning sonar pulses
//boolean dockingMode = false;
boolean boatDocked = false; //stores whether or not the dock has completed docking

float leftMotorDockVal;
float rightMotorDockVal;

//int dockingRegion;

void DockingMechanism() {
  incomingRadio();
  verifiedBoat = true;
  Serial.println("DWFEDSA");

  if (boatDocked == false) {
    switch (dockingRegion) {
      case 1:
        Serial.println("HELP");
        //Region A
        changeHeading;
        checkDist(); //Prevents us from getting too close
        break;
      case 2:
        //Region B
        // Turn right
        setMotors_dock(-80, 80); //DISCUSS AND CHANGE THESE VALUES
        delay (400);
        setMotors_dock(80, 80);
        delay(400);
        setMotors_dock(-80, -80);
        delay(10);
        break;
      case 3:
        //Region C
        //Turn left
       setMotors_dock(80, -80); //DISCUSS AND CHANGE THESE VALUES
        delay (400);
        setMotors_dock(80, 80);
        delay(400);
        setMotors_dock(-80, -80);
        delay(10);
        break;
      case 4:
        //Region D
        //Stop
        setMotors_dock(0, 0);
        break;
      case 5:
        //Region E
        //Go forward
        dockingMode = false;
      default:
        //error
        break;
    }
  }
}
