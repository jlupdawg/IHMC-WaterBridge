#include <math.h>

//const int (Pin-On-Sensor)_(Sensor-Number) = (Pin-On-Arduino)
const int Pin2_1 = 3;
const int Pin2_2 = 5;
const int Pin4_2 = 2; //trigger pin
const int ThermistorPin = 0;
double Sensor1, Sensor2, Distance1, Distance2, DistanceAverage;
double AmbientTemp; //Celcius
double CalibrationFactor;


void setup () {
  Serial.begin(9600);
  pinMode(Pin2_1, INPUT);
  pinMode(Pin2_2, INPUT);
  pinMode(Pin4_2, OUTPUT); //Using pin 2 for triggering asymetric firing of sonar sensor.
}

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

void Read_Sensor(){
  Sensor1 = pulseIn(Pin2_1, HIGH);
  Distance1 = Sensor1 / CalibrationFactorCalculation(); //makes the reported range the distance in centimeters
  
  delay(5); //helped make the range readings more stable
  
  Sensor2 = pulseIn(Pin2_2, HIGH);
  Distance2 = Sensor2 / CalibrationFactorCalculation();

  //DistanceAverage = (Distance1 + Distance2) / 2.00;
}

void Start_Sensor(){
  digitalWrite(Pin4_2,HIGH);
  delay(2);   //Trigger delay in ms
  digitalWrite(Pin4_2,LOW);
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void Print_All(){         
  Serial.print("S1: ");
  Serial.print(" ");
  Serial.print(Distance1);
  Serial.print(" ");
  Serial.print("S2: ");
  Serial.print(" ");
  Serial.print(Distance2); 
  /*
  Serial.print(" ");
  Serial.print("Avg: ");
  Serial.print(" ");
  Serial.print(DistanceAverage); 
  */
  Serial.println();
}

void loop () {
  Start_Sensor();
  Read_Sensor();
  Print_All();
  delay(15);  //delay before the void loop starts the section again.  Make this match the refresh rate times how ever many sensors are in the chain.  I typically add 10 to help with any secondary reflections
}
