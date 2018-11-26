//We want to get the boat in section A where both sensors can find it
//And theta and alpha and therefore desired heading can be found
//If it is not in section A, we must get it in section A
//Section A is the general region where both sensors can sense the boat

void findChar(){
  if(sonarDist1 < 2000 && sonarDist2 < 2000){
    //A
    }
  if(sonarDist1 < 2000 && sonarDist2 >= 2000){
    //B
    }
  if(sonarDist2 < 2000 && sonarDist1 >= 2000){
    //C
    }
  if(sonarDist1 >= 2000 && sonarDist2 >= 2000){
    //D
    }
  }

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
