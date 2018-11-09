void magX(char command){

    
    
    do
    {
      Read_Magn();   // X axis (magnetic sensor y axis)
      
      //Serial.println(imu.my);
      // Apply sensor calibration
    
      //compensate_sensor_errors(); //c
    
      //output_sensors_binary(); //c
      //output_sensors_text('C'); //t
    
      SerialPort.println(magnetom[0]);

      if(SerialPort.available()){
        command = SerialPort.read();
        }
      
    }
    while(command=='x');

  
  }
