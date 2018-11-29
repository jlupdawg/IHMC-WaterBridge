void CalibrationFactorCalculation() {
  double RawTemp = analogRead(0); //Reads raw temperature data, stores it in RawTemp

  AmbientTemp = log(10000.0 * ((1024.0 / RawTemp - 1))); //= log(10000.0/(1024.0/RawTemp-1)) // for pull-up configuration
  AmbientTemp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * AmbientTemp * AmbientTemp )) * AmbientTemp );
  AmbientTemp = AmbientTemp - 273.15;            // Convert Kelvin to Celcius

  CalibrationFactor = (1 / (331 + (0.6 * (AmbientTemp)))) * (20000); //Use SI units for calculation

  if (AmbientTemp >= 270 || AmbientTemp <= -270) { //Safeguard for failed Thermistor
    CalibrationFactor = 58.3; //STP calibration factor
  }
}

void Sonar_S1() {

  digitalWrite(TrigPinS1, LOW);
  delayMicroseconds(5); //Allows for the sound reflection to disipate before re-firing the sonar, it cleans up the interference

  digitalWrite(TrigPinS1, HIGH);
  delayMicroseconds(10); //Allows sound to travel to destination and back

  digitalWrite(TrigPinS1, LOW);

  duration = pulseIn(EchoPinS1, HIGH);
  distanceS1 = (duration / CalibrationFactor);

  if(distanceS1 < 2000){
      IdentifyObject();
    }
}

void Sonar_S2() {

  digitalWrite(TrigPinS2, LOW);
  delayMicroseconds(5); //Allows for the sound reflection to disipate before re-firing the sonar, it cleans up the interference

  digitalWrite(TrigPinS2, HIGH);
  delayMicroseconds(10); //Allows sound to travel to destination and back

  digitalWrite(TrigPinS2, LOW);

  duration = pulseIn(EchoPinS2, HIGH);
  distanceS2 = (duration / CalibrationFactor);

    if(distanceS2 < 2000){
      IdentifyObject();
    }
}

void IdentifyObject(){
//Sends out a sonar pulse
//Sends boat radio signal to listen for pulse
//Dock waits for transmission back that pulse was recieved

  digitalWrite(TrigPinS2, HIGH);
  sendRadio(); //send message to be sent to function sendRadio()
  delay(2); //Sends out 2 second pulse allowing time for boat to recieve pulse
  digitalWrite(TrigPinS2, LOW); //terminated pulse
    
  
  }

void calibrationFactorCalculation(){
  //Jacob what is this for?
  }

void findRegion(){
  if(distanceS1 < detectDist && distanceS2 < detectDist){
    //Zone A
    regionVariable=1;
    }
  if(distanceS1 < detectDist && distanceS2 >= detectDist){
    //Zone B
    regionVariable=2;
    }
  if(distanceS2 < detectDist && distanceS1 >= detectDist){
    //Zone C
    regionVariable=3;
    }
  if(distanceS1 >= detectDist && distanceS2 >= detectDist){
    //Zone D
    regionVariable=4;
    }
  }
