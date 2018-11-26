bool signalReceived == false;
//bool boatConfirmed == true; //We absolutely do not need this for the pool

char locationVariable; //char that is sent through radio

void setup() {
  //Setup radio for dock
}

void loop() {
  if (signalReceived && boatConfirmed){
    pingSonar();
    findChar(); //check to see if A, B, C, or D
    
    lawOfCosines(sonarDist1, sonarDist2, distBetweenSensors);
    findAlpha();
    getDesiredHeading();
    
    sendSignal();
    }

}
