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
float headingError;
boolean verifiedBoat; //stores whether the boat has confirmed that it is the object returning sonar pulses
boolean dockingMode;
boolean boatDocked; //stores whether or not the dock has completed docking

void DockingMechanism() {

  while (dockingMode){

    if(verifiedBoat == false){
      pulseSonar();
      }

    //readSensor1(); //Radio
    //readSensor2(); //Radio
    
    lawOfCosines(sonarDist1, sonarDist2, distBetweenSensors);
    findAlpha();

    getCurrentHeading();
    calculateDesiredHeading();//getDesiredHeading;
    
    changeHeading();

    if(boatDocked == false){
      checkDist();
      }
    
  }

  

}
