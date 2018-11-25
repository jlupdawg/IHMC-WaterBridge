void magX(char command){
  
    compensate_sensor_errors();

    do
    {
      magnetom[0] = imu.my;   // X axis (magnetic sensor y axis)
      magnetom[1] = -imu.mx;  // Y axis (magnetic sensor -x axis)
      magnetom[2] = imu.mz; // Z axis (magnetic sensor z axis)

      /*quat0 = (imu.calcQuat(imu.qw));
      quat1 = (imu.calcQuat(imu.qx));
      quat2 = (imu.calcQuat(imu.qy));
      quat3 = (imu.calcQuat(imu.qz));*/
      
      //Serial.println(imu.my);
      // Apply sensor calibration
    
      //compensate_sensor_errors(); //c
    
      //output_sensors_binary(); //c
      //output_sensors_text('C'); //t
    
      SerialPort.println(magnetom[0]);
      /*SerialPort.println(quat0);
      SerialPort.println(quat1);
      SerialPort.println(quat2);
      SerialPort.println(quat3);*/
      

      if(SerialPort.available()){
        command = SerialPort.read();
        }
      
    }
    while(command=='x');

  
  }
