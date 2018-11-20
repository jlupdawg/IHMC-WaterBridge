int CollisionWarning, Left = 0, Right = 0, Centered = 0; //LEft and Right are relative to the front sonar sensor/front of boat

double Override(int f1, int b1){ //
  int CollisionWarning;
  if(f1 <= 20.00){ //20centimeters
      CollisionWarning = 1; //if CollisionWarning equals 1 then there is an object within 20cm
    }
  else{
      CollisionWarning = 0; //No object within 20cm
    }
  
  //return CollisionWarning;
  }

void Object_Location(){

  if(leftMotor == 0 && rightMotor ==0){
    f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);
    b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);
  }
  
  if(leftMotor > 0 && rightMotor > 0){
    f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);
  }
  
  if(leftMotor < 0 && rightMotor < 0){
    b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);
  }
  
  if(f1 <= 20){
    s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s2 = SonarSensor_Corner(trigPin_2, echoPin_2);
    
    if(s1 < s2){
      Left = 1;
    }
    
    else if(s2 < s1){
      Right = 1;
    }
    
    else{
      Centered = 1;
    }
    
  }
  else{
    s1 = s2 = 0;
    }

  if(b1 <= 20){
    
    s3 = SonarSensor_Corner(trigPin_3, echoPin_3);
    s4 = SonarSensor_Corner(trigPin_4, echoPin_4);
    
    if(s3 < s4){
      Right = 1;
    }
    
    else if(s4 < s3){
      Left = 1;
    }
    
    else{
      Centered = 1;
    }
    
  }
  else{
    s3 = s4 = 0;
    }
  
}
