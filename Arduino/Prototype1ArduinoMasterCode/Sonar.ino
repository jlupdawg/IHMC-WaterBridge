
void SonarSensor_Front_Back(double CalibrationFactor) {
  CalibrationFactor = CalibrationFactor;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void cornerSonarCheck() {
  if (forward == 1) { //boat going forward

    s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s2 = SonarSensor_Corner(trigPin_2, echoPin_2);

    if (s2 < watchCircleRadius) { //calculated for the minimum distance so the boat can turn and not hit the object when turning
      if (s2 < s1) { //object is to the right side relative to front sensor
        Direction = 0;
        setMotors_Sonar();
      }
    }
    else if (s1 < watchCircleRadius) {
      if (s1 < s2) { //object is to the left side relative to front sensor
        Direction = 1;
        setMotors_Sonar();
      }
    }
    else { //Exits sonar mode
      objectIndicated = 0;
    }
  }

  else { //boat going backwards
    s3 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s4 = SonarSensor_Corner(trigPin_2, echoPin_2);

    if (s4 < watchCircleRadius) {
      if (s4 < s3) {//obj left relative to front
        Direction = 0;
        setMotors_Sonar();
      }
    }
    else if (s3 < watchCircleRadius) {
      if (s3 < s4) {
        Direction = 1; //Direction equals zero because the boat is moving in reverse so the motors need to go the opposite direction.
        setMotors_Sonar();
      }
    }
    else { //in an else condition is triggered, no object is near by, f1 or b1 should read greater than 100cm at this time.
      objectIndicated = 0;
    }
  }
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

void Object_Location() {

  if (leftMotorValue > 1500 || rightMotorValue > 1500) { // boat moving forward
    forward = 1;
    backwards = 0;
    notMoving = 0;

    f1 = SonarSensor_Front_Back(pinB_4, pinF_2); //Fire front sonar sensor

    if (f1 < 16) { //16cm is the minimum range of the front/back sonar sensors
      f1 = 3000; //Out of range value, sonar will never read this high
    }

    objectDetection();
  }

  else if (leftMotorValue < 1500) { //motors moving backwards
    forward = 0;
    backwards = 1;
    notMoving = 0;

    b1 = SonarSensor_Front_Back(pinB_4, pinB_2);

    if (b1 < 16) { //16cm is the minimum range of the front/back sonar sensors
      b1 = 3000; //Out of range value, sonar will never read this high
    }

    objectDetection();
  }

  else if (leftMotorValue == 1500 || rightMotorValue == 1500) { //if condition for when the motors are not spinning, boat could be drifting
    if (forward == 1) {
      forward = 0;
      notMoving = 1;
      f1 = SonarSensor_Front_Back(pinB_4, pinF_2);
      objectDetection();
    }

    else if (backwards == 1) {
      backwards = 0;
      notMoving = 1;
      b1 = SonarSensor_Front_Back(pinB_4, pinB_2);
      objectDetection();
    }
    else {
      Serial.println("Error - Boat sensing idication error: The boat is not moving, boat is not going backwards, and boat is not going forward, indication of movement is undefined.");
    }
  }
  else {
    f1 = 3000;
    b1 = 3000;
    s1 = s2 = 3000;
    s3 = s4 = 3000;

    objectDetection();
  }
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void objectDetection() { //function to compare read sonar values, this function will turn on objectIndicated to 1 if object is within the set distance to trigger(100cm), otherwise objectIndicated will equal 0

  if (f1 <= 100) { //distance in cm
    objectIndicated = 1;
    s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s2 = SonarSensor_Corner(trigPin_2, echoPin_2);

    if (s1 < s2) {
      Direction = 1; //object is to the left side relative to front sensor
    }

    else if (s2 < s1) {
      Direction = 0; //object is to the right side relative to front sensor
    }
    else {
      Direction = 2; //object is centered relative to front sensor
    }
  }
  else {
    objectIndicated = 0;
  }

  if (b1 <= 100) { //distance in cm
    objectIndicated = 1;
    s3 = SonarSensor_Corner(trigPin_3, echoPin_3);
    s4 = SonarSensor_Corner(trigPin_4, echoPin_4);

    if (s3 < s4) {
      Direction = 0; //object is to the right side relative to front sensor
    }

    else if (s4 < s3) {
      Direction = 1; //object is to the left side relative to front sensor
    }

    else {
      Direction = 2; //object is centered relative to front sensor
    }
  }
  else {
    objectIndicated = 0;
  }

}


double CalibrationFactorCalculation() {
  double RawTemp = analogRead(0); //Reads raw temperature data, stores it in RawTemp

  AmbientTemp = log(10000.0 * ((1024.0 / RawTemp - 1))); //= log(10000.0/(1024.0/RawTemp-1)) // for pull-up configuration
  AmbientTemp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * AmbientTemp * AmbientTemp )) * AmbientTemp );
  AmbientTemp = AmbientTemp - 273.15;            // Convert Kelvin to Celcius

  CalibrationFactor = (1 / (331 + (0.6 * (AmbientTemp)))) * (20000); //Use SI units for calculation

  if (AmbientTemp >= 270 || AmbientTemp <= -270) { //Safeguard for failed Thermistor
    CalibrationFactor = 58.3; //Factory calibration factor
  }

  return CalibrationFactor;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

int SonarSensor_Front_Back(int trigPin, int echoPin) {

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20); //trigger delay for reduced interference
  digitalWrite(trigPin, LOW);

  duration_front_back = pulseIn(echoPin, HIGH); //timeout is defualt 1 second add pulseIn(pin, HIGH/LOW, timeout) for specified time out
  distance_front_back = (distance_front_back / CalibrationFactor);
  delayMicroseconds(5); //helps make the distance readings more stable

  return distance_front_back;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

int SonarSensor_Corner(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5); //Allows for the sound reflection to disipate before re-firing the sonar, it cleans up the interference

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Allows sound to travel to destination and back

  digitalWrite(trigPin, LOW);

  duration_corner = pulseIn(echoPin, HIGH);
  distance_corner = (duration_corner / CalibrationFactor);

  return distance_corner;
}
