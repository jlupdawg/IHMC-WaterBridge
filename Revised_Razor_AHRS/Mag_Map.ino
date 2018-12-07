void mag_Map() {
  average_MAG_Heading *= 180 / PI;
  /////////////////////No Field Map////////////////////////////
  /*if(average_MAG_Heading <= 55){
    average_MAG_Heading = map(average_MAG_Heading, 0, 55, 0, 90);
    }
    else if(average_MAG_Heading <= 100){
    average_MAG_Heading = map(average_MAG_Heading, 55, 100, 90, 165);
    }
    else if(average_MAG_Heading <= 170){
    average_MAG_Heading = map(average_MAG_Heading, 100, 170, 165, 225);
    }
    else if(average_MAG_Heading <= 260){
    average_MAG_Heading = map(average_MAG_Heading, 170, 260, 225, 270);
    }
    else if(average_MAG_Heading <= 315){
    average_MAG_Heading = map(average_MAG_Heading, 260, 315, 270, 315);
    }
    else if(average_MAG_Heading <= 360){
    average_MAG_Heading = map(average_MAG_Heading, 315, 360, 315, 360);
    }*/

  //////////////////////////Boat Corner Map///////////////////////////////////
  if (average_MAG_Heading <= 20) {
    average_MAG_Heading = map(average_MAG_Heading, 0, 20, 90, 112.5);
  }
  else if (average_MAG_Heading <= 37.3) {
    average_MAG_Heading = map(average_MAG_Heading, 20, 37.3, 112.5, 135);
  }
  else if (average_MAG_Heading <= 53.3) {
    average_MAG_Heading = map(average_MAG_Heading, 37.3, 53.3, 135, 157.5);
  }
  else if (average_MAG_Heading <= 81) {
    average_MAG_Heading = map(average_MAG_Heading, 53.3, 81, 157.5, 180);
  }
  else if (average_MAG_Heading <= 107.7) {
    average_MAG_Heading = map(average_MAG_Heading, 81, 107.7, 180, 202.5);
  }
  else if (average_MAG_Heading <= 129) {
    average_MAG_Heading = map(average_MAG_Heading, 107.7, 129, 202.5, 225);
  else if (average_MAG_Heading <= 152.7) {
    average_MAG_Heading = map(average_MAG_Heading, 129, 152.7, 225, 247.5);
  }
  else if (average_MAG_Heading <= 181) {
    average_MAG_Heading = map(average_MAG_Heading, 152.7, 181, 247.5, 270);
  }
  else if (average_MAG_Heading <= 209.3) {
    average_MAG_Heading = map(average_MAG_Heading, 181, 209.3, 270, 292.5);
  }
  else if (average_MAG_Heading <= 230.7) {
    average_MAG_Heading = map(average_MAG_Heading, 209.3, 230.7, 292.5, 315);
  }
  else if (average_MAG_Heading <= 251.7) {
    average_MAG_Heading = map(average_MAG_Heading, 230.7, 251.7, 315, 337.5);
  }
  else if (average_MAG_Heading <= 280) {
    average_MAG_Heading = map(average_MAG_Heading, 251.7, 280, 337.5, 360);
  }
  else if (average_MAG_Heading <= 304.3) {
    average_MAG_Heading = map(average_MAG_Heading, 280, 304.3, 0, 22.5);
  }
  else if (average_MAG_Heading <= 320.3) {
    average_MAG_Heading = map(average_MAG_Heading, 304.3, 320.3, 22.5, 45);
  }
  else if (average_MAG_Heading <= 339) {
    average_MAG_Heading = map(average_MAG_Heading, 320.3, 339, 45, 67.5);
  }
  else if (average_MAG_Heading <= 360) {
    average_MAG_Heading = map(average_MAG_Heading, 339, 360, 67.5, 90);
  }
}
