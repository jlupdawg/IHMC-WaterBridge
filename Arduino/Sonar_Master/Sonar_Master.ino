#include <math.h>

#define trigPin_1 41
#define echoPin_1 39
#define trigPin_2 21
#define echoPin_2 23
#define trigPin_3 25
#define echoPin_3 27
#define trigPin_4 37
#define echoPin_4 35
// 5 6 11
//#define (Pin-On-Sensor)_(Sensor-Number) (Pin-On-Arduino)
#define Pin2_1 5
#define Pin2_2 6
#define Pin4_2 11 //trigger pin for both Front and Back Sensors


double duration, distance_corner, distance_front_back, s1, s2, s3, s4, f1, b1;
double CalibrationFactor;

void setup () {
  Serial.begin(9600);
  pinMode(trigPin_1, OUTPUT);
  pinMode(echoPin_1, INPUT);
  pinMode(trigPin_2, OUTPUT);
  pinMode(echoPin_2, INPUT);
  pinMode(trigPin_3, OUTPUT);
  pinMode(echoPin_3, INPUT);
  pinMode(trigPin_4, OUTPUT);
  pinMode(echoPin_4, INPUT);
  pinMode(Pin2_1, INPUT);
  pinMode(Pin2_2, INPUT);
  pinMode(Pin4_2, OUTPUT); //Using pin 2 for triggering asymetric firing of front and back sonar sensor.
  //pinMode(Pin4_1, OUTPUT);
  CalibrationFactor = CalibrationFactorCalculation(); //Approx. around 58
  SonarSensor_Front_Back(CalibrationFactor);
  SonarSensor_Corner(CalibrationFactor);
}

void loop () {
  //Override();
  f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);
  b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);
  
  if(f1 <= 20){
    s1 = SonarSensor_Corner(trigPin_1, echoPin_1);
    s2 = SonarSensor_Corner(trigPin_2, echoPin_2);
    if(s1 < s2){
      Serial.println("Left");
    }
    else if(s2 < s1){
      Serial.println("Right");
    }
    else{
      Serial.println("Centered");
    }
  }
  else{
    s1 = s2 = 0;
    }
  if(b1 <= 20){
    s3 = SonarSensor_Corner(trigPin_3, echoPin_3);
    s4 = SonarSensor_Corner(trigPin_4, echoPin_4);
    if(s3 < s4){
      Serial.println("Right");
    }
    else if(s4 < s3){
      Serial.println("Left");
    }
    else{
      Serial.println("Centered");
    }
  }
  else{
    s3 = s4 = 0;
    }
 
  /*Serial.print("s1: ");
  Serial.print(s1);
  Serial.print("   -   ");
  Serial.print("f1: ");
  Serial.print(f1);
  Serial.print("   -   ");
  Serial.print("s2: ");
  Serial.print(s2);
  Serial.print("   -   ");
  Serial.print("s3: ");
  Serial.print(s3);
  Serial.print("   -   ");
  Serial.print("b1: ");
  Serial.print(b1);
  Serial.print("   -   ");
  Serial.print("s4: ");
  Serial.println(s4);
  */

  Serial.print("f1: ");
  Serial.print(f1);
  Serial.print("   -   ");
  Serial.print("b1: ");
  Serial.println(b1);
  
  //delay(100);
}
