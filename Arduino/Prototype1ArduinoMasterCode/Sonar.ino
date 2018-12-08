
/*void SonarSensor_Front_Back(double CalibrationFactor) {
  CalibrationFactor = CalibrationFactor;
  }*/

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void cornerSonarCheck() {
  //Serial.println("cornerSonarCheck");
  if (forward == 1) { //boat going forward
    s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s2 = SonarSensor_Corner(trigPin_2, echoPin_2);

    if (s2 < watchCircleRadius) { //calculated for the minimum distance so the boat can turn and not hit the object when turning
      if (s2 < s1) { //object is to the right side relative to front sensor
        Direction = 0;
        return;
      }
      return;
    }
    else if (s1 < watchCircleRadius) {
      if (s1 < s2) { //object is to the left side relative to front sensor
        Direction = 1;
        return;
      }
    }
    else { //Exits sonar mode
      Serial.println("Indicator: Object drifted out of range of S1 or S2");
      objectIndicated = 0;
      return;
    }
    return;
  }
  /***********************************************************************************************************************/
  else if (backwards == 1) { //boat going backwards
    s3 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s4 = SonarSensor_Corner(trigPin_2, echoPin_2);

    if (s4 < watchCircleRadius) {
      if (s4 < s3) {//obj left relative to front
        Direction = 0;
        return;
      }
    }
    else if (s3 < watchCircleRadius) {
      if (s3 < s4) {
        Direction = 1; //Direction equals zero because the boat is moving in reverse so the motors need to go the opposite direction.
        return;
      }
    }
    else {
      Serial.println("Indicator: Object drifted out of range of S3 or S4");
      objectIndicated = 0;
      return;
    }
    return;
  }
  /***********************************************************************************************************************/
  else if (notMoving == 1) {

    forward = 0;
    backwards = 0;
    notMoving = 1;

    //f1 = SonarSensor_Front_Back(pinB_4, pinF_2);

    s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s2 = SonarSensor_Corner(trigPin_2, echoPin_2);

    if (s2 < watchCircleRadius) { //calculated for the minimum distance so the boat can turn and not hit the object when turning
      objectIndicated = 1;
      if (s2 < s1) { //object is to the right side relative to front sensor
        Direction = 0;
        return;
      }
      return;
    }
    else if (s1 < watchCircleRadius) {
      objectIndicated = 1;
      if (s1 < s2) { //object is to the left side relative to front sensor
        Direction = 1;
        return;
      }
    }
    else if (f1 >= 100) { //Exits sonar mode
      Serial.println("Indicator: Object drifted out of range of S1 or S2");
      objectIndicated = 0;
      return;
    }
    //cornerSonarCompare();//NEW
    objectDetection();
    return;
  }
  return;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

void Object_Location() {
  //Serial.println("Object_Location");

  if (leftMotorValue > 1500 && rightMotorValue > 1500) { //****************************Motor Condition - Forward
    forward = 1;
    backwards = 0;
    notMoving = 0;

    f1 = SonarSensor_Front_Back(pinB_4, pinF_2); //Fire front sonar sensor

    objectDetection();
    return;
  }

  else if (leftMotorValue > 1500 && rightMotorValue < 1500) {//****************************Motor Condition - Right Turn
    if (forward == 1) {
      f1 = SonarSensor_Front_Back(pinB_4, pinF_2);
      backwards = 0;
      notMoving = 0;
      objectDetection();
      return;
    }
    else if (backwards == 1) {
      b1 = SonarSensor_Front_Back(pinB_4, pinB_2);
      forward = 0;
      notMoving = 0;
      objectDetection();
      return;
    }
    else {
      Serial.println("Error 1: Object_Location() - F1/B1 Sonar Not Fired");
      f1 = 3000;
      b1 = 3000;
      s1 = s2 = 3000;
      s3 = s4 = 3000;
      //add else if statement for noMoving = 1;
      forward = 1;
      objectDetection();
      return;
    }
    return;
  }

  else if (leftMotorValue < 1500 && rightMotorValue > 1500) {//****************************Motor Condition - Left Turn
    if (forward == 1) {
      f1 = SonarSensor_Front_Back(pinB_4, pinF_2);
      objectDetection();
      return;
    }
    else if (backwards == 1) {
      b1 = SonarSensor_Front_Back(pinB_4, pinB_2);
      objectDetection();
      return;
    }
    else {
      Serial.println("Error 2: Object_Location() - F1/B1 Sonar Not Fired");
      f1 = 3000;
      b1 = 3000;
      s1 = s2 = 3000;
      s3 = s4 = 3000;
      forward = 1;
      objectDetection();
      return;
    }
    return;
  }

  else if (leftMotorValue < 1500 && rightMotorValue < 1500) {//****************************Motor Condition - Backwards
    forward = 0;
    backwards = 1;
    notMoving = 0;
    b1 = SonarSensor_Front_Back(pinB_4, pinB_2);
    objectDetection();
    return;
  }

  else if (leftMotorValue == 1500 && rightMotorValue == 1500) { //****************************Motor Condition - No motor speed
    if (forward == 1) {
      Serial.println("Habala badingdong dingding dang");
      backwards = 0;
      forward = 0;
      notMoving = 1;
      f1 = SonarSensor_Front_Back(pinB_4, pinF_2);
      objectDetection();
      return;
    }

    else if (backwards == 1) {
      forward = 0;
      backwards = 0;
      notMoving = 1;
      b1 = SonarSensor_Front_Back(pinB_4, pinB_2);
      objectDetection();
      return;
    }
    else if (notMoving == 3) {
      Serial.println("Boat start up: No change in motor values indicated, firing front sonar");

      forward = 1;
      backwards = 0;
      notMoving = 0;
      //f1 = SonarSensor_Front_Back(pinB_4, pinF_2); OLD

      frontBackCompare(); //NEW*************

      //objectDetection(); OLD
      return;
    }
    else { //boat notMoving = 1;
      //Serial.println("PRINT 3");
      forward = 0;
      backwards = 0;
      notMoving = 1;

      //f1 = SonarSensor_Front_Back(pinB_4, pinF_2); OLD
      frontBackCompare(); //NEW********************************

      //objectDetection(); OLD
      return;
    }
    return;
  }
  else {
    Serial.println("CRITICAL ERROR: No motor values, motors sheared off boat.");
    f1 = 3000;
    b1 = 3000;
    s1 = s2 = 3000;
    s3 = s4 = 3000;
    objectDetection();
    return;
  }
  return;
}
/****************************************************************NEW BELOW********************************************************************/
void frontBackCompare() {
  f1 = SonarSensor_Front_Back(pinB_4, pinF_2);
  delayMicroseconds(12);
  b1  = SonarSensor_Front_Back(pinB_4, pinB_2);
  if (f1 < b1) {
    backwards = 1;
    objectDetection();
  }
  if (b1 < f1) {
    forward = 1;
    objectDetection();
  }
}

void cornerSonarCompare() {
  
  //NEW BELOW 12/7/18 7:00PM
  s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
  delayMicroseconds(5);
  s2 = SonarSensor_Corner(trigPin_2, echoPin_2);
  delayMicroseconds(5);
  s3 = SonarSensor_Corner(trigPin_3, echoPin_3);
  delayMicroseconds(5);
  s4 = SonarSensor_Corner(trigPin_4, echoPin_4);
  delayMicroseconds(5);
  f1 = SonarSensor_Front_Back(pinB_4, pinF_2);
  delayMicroseconds(12);
  b1  = SonarSensor_Front_Back(pinB_4, pinB_2);
  //NEW ABOVE 12/7/18 7:00PM
  if ((s1 < watchCircleRadius) || (s4 < watchCircleRadius)) {
    if (s1 < s4) {
      backwards = 1;
      Direction = 1;
    }
    if (s4 < s1) {
      forward = 1;
      Direction = 1;
    }
  }
  else if ((s2 < watchCircleRadius) || (s3 < watchCircleRadius)) {
    if (s2 < s3) {
      backwards = 1;
      Direction = 0;
    }
    if (s3 < s2) {
      forward = 1;
      Direction = 0;
    }
  }
  else {
    return;
  }
  //NEW BELOW 12/7/18 7:10PM
  if ((s1 < watchCircleRadius) && (s4 < watchCircleRadius) && (f1 < watchCircleRadius)) {
    Direction = 0;
    backwards = 1;
  }
  else if ((s2 < watchCircleRadius) && (s3 < watchCircleRadius) && (f1 < watchCircleRadius)) {
    Direction = 1;
    backwards = 1;
  }
  else if ((s1 < watchCircleRadius) && (s4 < watchCircleRadius) && (b1 < watchCircleRadius)) {
    Direction = 0;//0 is left motor minimum right motor max, 1 is left max, right min
    forward = 1;
  }
  else if ((s2 < watchCircleRadius) && (s3 < watchCircleRadius) && (b1 < watchCircleRadius)) {
    Direction = 1;
    forward = 1;
  }
  else {
    return;
  }
  //NEW ABOVE 12/7/18 7:10PM
  
}
/****************************************************************NEW ABOVE********************************************************************/

void megaBroke() {
  Serial.println("megaBroke");

  forward = 1;
  notMoving = 0;
  backwards = 0;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
void objectDetection() { //function to compare read sonar values, this function will turn on objectIndicated to 1 if object is within the set distance to trigger(100cm), otherwise objectIndicated will equal 0
  //Serial.println("objectDetection");
  if (f1 <= watchCircleRadius) { //distance in cm
    objectIndicated = 1;
    s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s2 = SonarSensor_Corner(trigPin_2, echoPin_2);

    if (s1 < s2) {
      Direction = 1; //object is to the left side relative to front sensor
      return;
    }

    else if (s2 < s1) {
      Direction = 0; //object is to the right side relative to front sensor
      return;
    }
    else {
      Direction = 2; //object is centered relative to front sensor
      return;
    }
    return;
  }

  else if (b1 <= watchCircleRadius) { //distance in cm
    objectIndicated = 1;
    s3 = SonarSensor_Corner(trigPin_3, echoPin_3);
    s4 = SonarSensor_Corner(trigPin_4, echoPin_4);

    if (s3 < s4) {
      Direction = 0; //object is to the right side relative to front sensor
      return;
    }

    else if (s4 < s3) {
      Direction = 1; //object is to the left side relative to front sensor
      return;
    }

    else {
      Direction = 2; //object is centered relative to front sensor
      return;
    }
    return;
  }
  else {
    objectIndicated = 0;
    return;
  }
  return;
}

double CalibrationFactorCalculation() {
  //Serial.println("CalibrationFactorCalculation");
  double RawTemp = analogRead(0); //Reads raw temperature data, stores it in RawTemp

  AmbientTemp = log(10000.0 * ((1024.0 / RawTemp - 1))); //= log(10000.0/(1024.0/RawTemp-1)) // for pull-up configuration
  AmbientTemp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * AmbientTemp * AmbientTemp )) * AmbientTemp );
  AmbientTemp = AmbientTemp - 273.15;            // Convert Kelvin to Celcius

  CalibrationFactor = (1 / (331 + (0.6 * (AmbientTemp)))) * (20000); //Use SI units for calculation

  if (AmbientTemp >= 270 || AmbientTemp <= -270) { //Safeguard for failed Thermistor
    CalibrationFactor = 58.3; //Factory calibration factor
  }
  CalibrationFactor = 58.3;
  return CalibrationFactor;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/
double tempVar;
int SonarSensor_Front_Back(int trigPin, int echoPin) {
  //Serial.println("SonarSensor_Front_Back");
  //Serial.println("PRINT 4");

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(12); //trigger delay for reduced interference
  digitalWrite(trigPin, LOW);

  duration_front_back = pulseIn(echoPin, HIGH); //timeout is defualt 1 second add pulseIn(pin, HIGH/LOW, timeout) for specified time out
  tempVar = (duration_front_back / CalibrationFactor);

  if (tempVar != 0) {
    distance_front_back = tempVar;
  }
  //Serial.print("duration: "); Serial.println(duration_front_back);
  //delayMicroseconds(10000);

  //delayMicroseconds(50); //helps make the distance readings more stable

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
