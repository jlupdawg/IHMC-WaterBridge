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
boolean boatDocked; //stores whether or not the dock has completed docking

float leftMotorDockVal;
float rightMotorDockVal;

//int dockingRegion;

void DockingMechanism() {
  incomingRadio();

  if (verifiedBoat == false) {
    pulseSonar();
  }
  else if(boatDocked == true){
    //Do nothing
    }
  else if(boatDocked == false && dockingRegion == '1') {
    switch (dockingRegion) {
      case 1:
        //Region A
        changeHeading;
        checkDist(); //Prevents us from getting too close
        break;
      case 2:
        //Region B
        // Turn right
        setMotors_dock(0, 15); //DISCUSS AND CHANGE THESE VALUES
        break;
      case 3:
        //Region C
        //Turn left
        setMotors_dock(15, 0); //DISCUSS AND CHANGE THESE VALUES
        break;
      case 4:
        //Region D
        //Stop
        //setMotors_dock(0, 0);
        break;
      case 5:
        //Region E
        //Go forward
        setMotors_dock(15, 15);
      default:
        //error
        break;
    }
  }
  else{
    //Error
  }

}
