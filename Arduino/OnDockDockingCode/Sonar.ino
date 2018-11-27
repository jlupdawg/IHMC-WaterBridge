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
  DistanceS1 = (duration / CalibrationFactor);

  if(DistanceS1 < 2000){
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
  DistanceS2 = (duration / CalibrationFactor);

    if(DistanceS2 < 2000){
      IdentifyObject();
    }
}

IdentifyObject(){
//Sends out a sonar pulse
//Sends boat radio signal to listen for pulse
//Dock waits for transmission back that pulse was recieved

  digitalWrite(TrigPinS2, HIGH);
  sendRadio(); //send message to be sent to function sendRadio()
  delay(2); //Sends out 2 second pulse allowing time for boat to recieve pulse
  digitalWrite(TrigPinS2, LOW); //terminated pulse
    
  
  }

void findRegion(){
  if(DistanceS1 < 2000 && sonarDist2 < 2000){
    //A
    }
  if(DistanceS1 < 2000 && sonarDist2 >= 2000){
    //B
    }
  if(DistanceS2 < 2000 && DistanceS1 >= 2000){
    //C
    }
  if(DistanceS1 >= 2000 && DistanceS2 >= 2000){
    //D
    }
  }
