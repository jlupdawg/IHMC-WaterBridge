void SonarSensor_Front_Back(double CalibrationFactor) {
  CalibrationFactor = CalibrationFactor;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

void Object_Location() {

  int difference = 0;
  int tolerance = 20;
  avoid = false;

  if (leftMotorValue == 1500 && rightMotorValue == 1500) {
    f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);
    b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);
  }

  if (leftMotorValue > 1500 && rightMotorValue > 1500) {
    f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);

    if (f1 <= obstical_distance) {
      avoid = true;
      s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
      s2 = SonarSensor_Corner(trigPin_2, echoPin_2);
      difference = s2 - s1;
      if (difference > tolerance) {
        Direction = 1; // 1 equals Left
      }

      else if (difference < -tolerance) {
        Direction = 0; //0 equals Right
      }
      else {
        Direction = 2; // 2 equals centered
      }
      if (Direction != 2)
      {
        setMotors_Sonar();

      }
      else {
        s1 = s2 = 0;
      }
    }
  }
  if (leftMotorValue < 1500 && rightMotorValue < 1500) {
    b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);

    if (b1 <= obstical_distance) {
      avoid = true;
      s3 = SonarSensor_Corner(trigPin_3, echoPin_3);
      s4 = SonarSensor_Corner(trigPin_4, echoPin_4);
      difference = s4 - s3;
      if (difference > tolerance) {
        Direction = 0;
      }

      else if (difference < -tolerance) {
        Direction = 1;
      }

      else {
        Direction = 2;
      }

      setMotors_Sonar();

    }
    else {
      s3 = s4 = 0;
    }
  }

}

/*------------------------------------------------------------------------------------------------------------------------------------------------------*/

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
  delayMicroseconds(500); //trigger delay for reduced interference
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance_front_back = (duration / CalibrationFactor);
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

  duration = pulseIn(echoPin, HIGH);
  distance_corner = (duration / CalibrationFactor);

  return distance_corner;
}
