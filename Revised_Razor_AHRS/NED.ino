void accelerometer_NED(){
  
  Matrix_Vector_Multiply(DCM_Matrix, accel, aNED);
  
  aNorth = aNED[0];
  aEast = aNED[1];
  aDown = aNED[2];
  
  aDown -= GRAVITY;

  aNorth *= 9.81 / GRAVITY;
  aEast *= 9.81 / GRAVITY;
  aDown *= 9.81 / GRAVITY;
  
  }

void output_acc_NED(){
  
  SerialPort.print("NED Acceleration: "); SerialPort.print(aNorth); SerialPort.print(", ");
  SerialPort.print(aEast); SerialPort.print(", ");
  SerialPort.print(aDown); SerialPort.println(", "); SerialPort.println(" ");

  SerialPort.print("Heading: "); SerialPort.print(average_MAG_Heading * 180 / PI ); SerialPort.println(" ");

  delay(100);
  }
