void mag_Map(){
  average_MAG_Heading *= 180 / PI;
  
  SerialPort.print("Before: "); SerialPort.println(average_MAG_Heading);
  
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
  else if(average_MAG_Heading <= 360){
    average_MAG_Heading = map(average_MAG_Heading, 260, 360, 270, 360);
    }

  SerialPort.print("After: "); SerialPort.println(average_MAG_Heading);
  }
