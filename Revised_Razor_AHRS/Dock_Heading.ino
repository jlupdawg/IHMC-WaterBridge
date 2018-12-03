void dock_Heading(){

  headingAvg = numHead * headingAvg;
  headingAvg = headingAvg + average_MAG_Heading * 180 / PI;
  ++numHead;
  headingAvg = headingAvg / numHead;

  SerialPort.print(headingAvg); SerialPort.println("");

  /*if(numHead=60){
    numHead = 0;
    headingAvg = 0;
    }*/
  
  }
