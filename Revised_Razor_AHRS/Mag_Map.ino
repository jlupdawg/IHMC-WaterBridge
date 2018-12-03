void mag_Map(){
  average_MAG_Heading *= 180 / PI;
  
  if(average_MAG_Heading <= 55){
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
    }
  }
