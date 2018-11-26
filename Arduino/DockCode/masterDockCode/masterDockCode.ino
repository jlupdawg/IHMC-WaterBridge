float sonarDist1;
float sonarDist2;
float distBetweenSensors = 1; //distance in meters

float alpha;
float theta;
float dockDirection; //"heading" of dock (we should do this according to IMU!)
float desiredHeading;

boolean signalReceived = false;
bool boatConfirmed = true; //We absolutely do not need this for the pool

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
    calculateDesiredHeading();
    
    sendSignal();
    }

}
