void changeHeading(){
  
  if(currentHeading<desiredHeading){
    
    
    
    }

  else if(currentHeading>desiredHeading){
    
    
    
    }
  
  }

void checkDist(){
  
  if(sonarDist1 < dockingValue || sonarDist2 < dockingValue){
    //stopMotors();
    boatDocked = true;
    }
  
  }

void incrementMotors(int leftIncVal, int rightIncVal){

  leftIncVal = map(leftIncVal, -100, 100, minSpeed, maxSpeed);
  rightIncVal = map(rightIncVal, -100, 100, minSpeed, maxSpeed);
  
  leftMotorValue += leftIncVal;
  rightMotorValue += rightIncVal;
  
  leftMotorValue = constrain(leftMotorValue, minSpeed, maxSpeed);
  rightMotorValue = constrain(rightMotorValue, minSpeed, maxSpeed);

  leftMotor.writeMicroseconds(leftMotorValue);
  rightMotor.writeMicroseconds(rightMotorValue);
  
  }
