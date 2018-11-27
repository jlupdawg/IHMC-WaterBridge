float sonarDist1; //holds the distances sensed by the dock sonars
float sonarDist2;

float dockingValue = 20; //maximum sonar distance to consider boat "docked"

float distBetweenSensors; //distance between the mounted sensors

float theta; //angle between the sonar pulses
float alpha; //angle between triangle created by sonar pulses and the vector negative of the direction the dock is facing

float headingError;
float desiredHeading;
float currentHeading;
float dockDirection; //vector in the direction the dock is facing

boolean verifiedBoat; //stores whether the boat has confirmed that it is the object returning sonar pulses
//boolean dockingMode = false;
boolean boatDocked; //stores whether or not the dock has completed docking

char dockingSection;

void DockingMechanism() {

  if (verifiedBoat == false) {
    pulseSonar();
  }
  else if(boatDocked == false && boatDocked == 'A') {

    //readSensor1(); //Radio
    //readSensor2(); //Radio

    //lawOfCosines(sonarDist1, sonarDist2, distBetweenSensors); //ON DOCK
    //findAlpha(); //ON DOCK

    //getCurrentHeading();
    //calculateDesiredHeading();//getDesiredHeading; //ON DOCK

    changeHeading();

    checkDist();
  }

  else if(boatDocked == false && boatDocked == 'B'){
    //Turn right
  }
  else if(boatDocked == false && boatDocked == 'C'){
    //Turn left
  }
  else if(boatDocked == false && boatDocked == 'D'){
    //docked
    //Stop
    //In the dock code we should make it so that the dock is unable to send D unless it was previously B or C
    //boatDocked=true;
  }
  else if(boatDocked == true){
    Do nothing
  }
  else{
    //Error
  }

}
