void SonarSensor_Corner(double CalibrationFactor){
  CalibrationFactor = CalibrationFactor;
  }

int SonarSensor_Corner(int trigPin,int echoPin){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5); //Allows for the sound reflection to disipate before re-firing the sonar, it cleans up the interference

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //Allows sound to travel to destination and back

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance_corner = (duration / CalibrationFactor);

  return distance_corner;
}
