const int ThermistorPin = 0;
double AmbientTemp; //Celcius

double CalibrationFactorCalculation(){
  double RawTemp = analogRead(0); //Reads raw temperature data, stores it in RawTemp
  
  AmbientTemp = log(10000.0*((1024.0/RawTemp-1))); //= log(10000.0/(1024.0/RawTemp-1)) // for pull-up configuration
  AmbientTemp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * AmbientTemp * AmbientTemp ))* AmbientTemp );
  AmbientTemp = AmbientTemp - 273.15;            // Convert Kelvin to Celcius
    
  CalibrationFactor = (1 / (331 + (0.6 * (AmbientTemp)))) * (20000); //Use SI units for calculation
  
  if(AmbientTemp >= 270 || AmbientTemp <= -270){ //Safeguard for failed Thermistor
      CalibrationFactor = 58.3; //Factory calibration factor
    }
    
  return CalibrationFactor;
  }
