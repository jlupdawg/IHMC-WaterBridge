void SonarSensor_Front_Back(double CalibrationFactor){
  CalibrationFactor = CalibrationFactor;
  }

int SonarSensor_Front_Back(int trigPin,int echoPin){

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(500); //trigger delay for reduced interference
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance_front_back = (duration / CalibrationFactor);
  delayMicroseconds(5); //helps make the distance readings more stable

  delay(100);
  return distance_front_back;
}
