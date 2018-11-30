//We want to get the boat in section A where both sonar sensors can find it
//And theta and alpha and therefore desired heading can be found
//If it is not in section A, we must get it in section A
//Section A is the general region where both sensors can sense the boat

void lawOfCosines(float a, float b, float c){
  
  theta = acos((a*a + b*b - c*c) / (2*a*b));
  theta *= 180 / PI;
  //a is the magnitude of the reading from sensor 1
  //b is the magnitude of the reading from sensor 2
  //c is the distance between the sensors
  Serial.print("Theta: "); Serial.println(theta);
  }

void findAlpha(){
   
  alpha = distanceS1 * sin((theta * PI /180)) / distBetweenSensors - 90;
  alpha = abs(alpha);
  Serial.print("Alpha: "); Serial.println(alpha);
  
  }

void calculateDesiredHeading(){

  desiredHeading = 180 - dockDirection + theta/2 + alpha;

  Serial.print("Desired heading: "); Serial.println(desiredHeading);
  
  }
