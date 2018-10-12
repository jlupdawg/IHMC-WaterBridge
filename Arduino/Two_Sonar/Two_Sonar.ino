
const int pwPin1 = 3;
const int pwPin2 = 5;
int triggerPin1 = 2; //trigger pin to tell one sensor to fire at a delayed rate to avoid interference
double sensor1, sensor2, distance1, distance2;

void setup () {
  Serial.begin(9600);
  pinMode(pwPin1, INPUT);
  pinMode(pwPin2, INPUT);
  pinMode(triggerPin1, OUTPUT);
}

double AmbientTemp; //Celcius
double CalibrationFactor;
int ThermistorPin = A0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

double CalibrationFactorCalculation(){
    
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  AmbientTemp = T - 273.15; //celcius
       
  CalibrationFactor = (1 / (331 + 0.6 * (AmbientTemp))) * (20000); //Use SI units for calculation
  return CalibrationFactor;
  }

void read_sensor(){
  sensor1 = pulseIn(pwPin1, HIGH);
  distance1 = sensor1 / CalibrationFactorCalculation(); //makes the reported range the distance in centimeters
  delay(10); //helped make the range readings more stable
  sensor2 = pulseIn(pwPin2, HIGH);
  distance2 = sensor2 / CalibrationFactorCalculation();
}

void start_sensor(){
  digitalWrite(triggerPin1,HIGH);
  delay(5);   //delay between triggering the sensor that has UNO pin 2 to 4 on the sensor
  digitalWrite(triggerPin1,LOW);
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall(){         
  Serial.print("S1: ");
  Serial.print(" ");
  Serial.print(distance1);
  Serial.print(" ");
  Serial.print("S2: ");
  Serial.print(" ");
  Serial.print(distance2); 
  Serial.println();
}

void loop () {
  start_sensor();
  read_sensor();
  printall();
  delay(20);  //delay before the void loop starts the section again.  Make this match the refresh rate times how ever many sensors are in the chain.  I typically add 10 to help with any secondary reflections
}
