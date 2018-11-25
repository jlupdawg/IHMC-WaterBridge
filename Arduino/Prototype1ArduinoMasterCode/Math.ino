void lawOfCosines(float a, float b, float c){
  
  theta = acos((a*a + b*b - c*c) / (2*a*b));
  //a is the magnitude of the reading from sensor 1
  //b is the magnitude of the reading from sensor 2
  //c is the distance between the sensors
  
  }

void findAlpha(){
   
  alpha = sonarDist1 * sin(theta) / distBetweenSensors - 90;
  
  }

void calculateDesiredHeading(){

  desiredHeading = 180 - dockDirection + theta/2 + alpha;
  
  }
