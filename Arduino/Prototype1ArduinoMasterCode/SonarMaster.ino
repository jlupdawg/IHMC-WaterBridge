int Direction = 3; //Left and Right are relative to the front sonar sensor/front of boat


void Object_Location() {

  if (leftMotorValue == 1500 && rightMotorValue == 1500) {
    f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);
    b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);
  }

  if (leftMotorValue > 1500 && rightMotorValue > 1500) {
    f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);

    if (f1 <= 20) {
      s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
      s2 = SonarSensor_Corner(trigPin_2, echoPin_2);

      if (s1 < s2) {
        Direction = 1; // 1 equals Left
      }

      else if (s2 < s1) {
        Direction = 0; //0 equals Right
      }
      else {
        Direction = 2; // 2 equals centered
      }
    }
    else {
      s1 = s2 = 0;
    }
  }
  if (leftMotorValue < 1500 && rightMotorValue < 1500) {
    b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);

    if (b1 <= 20) {
      s3 = SonarSensor_Corner(trigPin_3, echoPin_3);
      s4 = SonarSensor_Corner(trigPin_4, echoPin_4);

      if (s3 < s4) {
        Direction = 0;
      }

      else if (s4 < s3) {
        Direction = 1;
      }

      else {
        Direction = 2;
      }
    }
    else {
      s3 = s4 = 0;
    }
  }
}
