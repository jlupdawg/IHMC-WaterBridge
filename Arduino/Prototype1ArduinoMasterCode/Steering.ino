void changeHeading(){
  
  /*if(currentHeading<desiredHeading){
    incrementMotors(-.01, .01);
    }

  else if(currentHeading>desiredHeading){
    incrementMotors(.01, -.01);
    }*/
    float difference;
    difference = currentHeading - desiredHeading;
    if (abs(difference) > 180){
      if(difference>0){
        difference -= 360;
        }
      else{
        difference +=360;
        }
      }
    
    if(difference > 180){
      difference = -difference;
      }
    incrementMotors((-difference)/100, (difference)/100); //increment both motors by a factor relating to the difference in heading
  }

void checkDist(){
  
  if(sonarDist1 < dockingValue || sonarDist2 < dockingValue){
    setMotors_dock(0,0);
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
