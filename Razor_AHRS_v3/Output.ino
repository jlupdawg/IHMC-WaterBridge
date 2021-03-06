/* This file is part of the Razor AHRS Firmware */
// Output angles: yaw, pitch, roll
void output_angles()
{
  if (output_format == 1)//OUTPUT__FORMAT_BINARY)
  {
	float ypr[3];
	ypr[0] = TO_DEG(average_MAG_Heading);
	ypr[1] = TO_DEG(average_pitch);
	ypr[2] = TO_DEG(average_roll);
	SerialPort.write((byte*) ypr, 12);  // No new-line
  }
  else if (output_format == OUTPUT__FORMAT_TEXT)
  {
	  SerialPort.print("#"); SerialPort.print(","); SerialPort.print(TO_DEG(average_roll)); SerialPort.print(",");
	  SerialPort.print(TO_DEG(average_pitch)); SerialPort.print(","); SerialPort.println(TO_DEG(average_MAG_Heading));
  }
}

void output_calibration(int calibration_sensor)
{
  if (calibration_sensor == 0)  // Accelerometer
  {
    // Output MIN/MAX values
    SerialPort.print("accel x,y,z (min/max) = ");
    for (int i = 0; i < 3; i++) {
      if (accel[i] < accel_min[i]) accel_min[i] = accel[i];
      if (accel[i] > accel_max[i]) accel_max[i] = accel[i];
      SerialPort.print(accel_min[i]);
      SerialPort.print("/");
      SerialPort.print(accel_max[i]);
      if (i < 2) SerialPort.print("  ");
      else SerialPort.println();
    }
  }
  else if (calibration_sensor == 1)  // Magnetometer
  {
    // Output MIN/MAX values
    SerialPort.print("magn x,y,z (min/max) = ");
    for (int i = 0; i < 3; i++) {
      if (magnetom[i] < magnetom_min[i]) magnetom_min[i] = magnetom[i];
      if (magnetom[i] > magnetom_max[i]) magnetom_max[i] = magnetom[i];
      SerialPort.print(magnetom_min[i]);
      SerialPort.print("/");
      SerialPort.print(magnetom_max[i]);
      if (i < 2) SerialPort.print("  ");
      else SerialPort.println();
    }
  }
  else if (calibration_sensor == 2)  // Gyroscope
  {
    // Average gyro values
    for (int i = 0; i < 3; i++)
      gyro_average[i] += gyro[i];
    gyro_num_samples++;
      
    // Output current and averaged gyroscope values
    SerialPort.print("gyro x,y,z (current/average) = ");
    for (int i = 0; i < 3; i++) {
      SerialPort.print(gyro[i]);
      SerialPort.print("/");
      SerialPort.print(gyro_average[i] / (float) gyro_num_samples);
      if (i < 2) SerialPort.print("  ");
      else SerialPort.println();
    }
  }
}

void output_sensors_text(char raw_or_calibrated)
{
  SerialPort.print("#A-"); SerialPort.print(raw_or_calibrated); SerialPort.print('=');
  SerialPort.print(accel[0]/GRAVITY); SerialPort.print(",");
  SerialPort.print(accel[1]/GRAVITY); SerialPort.print(",");
  SerialPort.print(accel[2]/GRAVITY); SerialPort.println();

  SerialPort.print("#M-"); SerialPort.print(raw_or_calibrated); SerialPort.print('=');
  SerialPort.print(magnetom[0]); SerialPort.print(",");
  SerialPort.print(magnetom[1]); SerialPort.print(",");
  SerialPort.print(magnetom[2]); SerialPort.println();

  SerialPort.print("#G-"); SerialPort.print(raw_or_calibrated); SerialPort.print('=');
  SerialPort.print(gyro[0]); SerialPort.print(",");
  SerialPort.print(gyro[1]); SerialPort.print(",");
  SerialPort.print(gyro[2]); SerialPort.println();
}

void output_sensors_binary()
{
  SerialPort.write((byte*) accel,12);
  SerialPort.write((byte*) magnetom, 12);
  SerialPort.write((byte*) gyro, 12);
}

void output_sensors()
{
  if (output_mode == OUTPUT__MODE_SENSORS_RAW)
  {
    if (output_format == OUTPUT__FORMAT_BINARY)
      output_sensors_binary();
    else if (output_format == OUTPUT__FORMAT_TEXT)
      output_sensors_text('R');
  }
  else if (output_mode == OUTPUT__MODE_SENSORS_CALIB)
  {
    // Apply sensor calibration
    compensate_sensor_errors();
    
    if (output_format == 1) //OUTPUT__FORMAT_BINARY)
      output_sensors_binary();
    else if (output_format == OUTPUT__FORMAT_TEXT)
      output_sensors_text('C');
  }
  else if (output_mode == OUTPUT__MODE_SENSORS_BOTH)
  {
    if (output_format == 1) // OUTPUT__FORMAT_BINARY)
    {
      output_sensors_binary();
      compensate_sensor_errors();
      output_sensors_binary();
    }
    else if (output_format == OUTPUT__FORMAT_TEXT)
    {
      output_sensors_text('R');
      compensate_sensor_errors();
      output_sensors_text('C');
    }
  }
  delay(1000);
}

void output_acc_NED(){
  
  /*SerialPort.print(aNorth); SerialPort.print(", ");
  SerialPort.print(aEast); SerialPort.print(", ");
  SerialPort.println(aDown); SerialPort.print(", ");*/

  /*SerialPort.print(accel[0]/9.8); SerialPort.print(", ");
  SerialPort.print(accel[1]/9.8); SerialPort.print(", ");
  SerialPort.println(accel[2]/9.8); SerialPort.print(", ");*/
  
  }

