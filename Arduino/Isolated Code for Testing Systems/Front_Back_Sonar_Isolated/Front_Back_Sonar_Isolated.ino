#include <math.h>

#define trigPin_1 41
#define echoPin_1 39
#define trigPin_2 21
#define echoPin_2 23
#define trigPin_3 25
#define echoPin_3 27
#define trigPin_4 37
#define echoPin_4 35

//#define (Pin-On-Sensor)_(Sensor-Number) (Pin-On-Arduino)
#define pinF_2 5      //Front sonar echo pin
#define pinB_2 6      //Back sonar echo pin
#define pinB_4 11     //F_B sonar trigger pin

double duration, distance_corner, distance_front_back, s1, s2, s3, s4, f1, b1;
double CalibrationFactor;

void setup() {
  Serial.begin(115200);

  pinMode(pinF_2, INPUT);
  pinMode(pinB_2, INPUT);
  pinMode(pinB_4, OUTPUT); //--------------------------------------------------------------------------------uses pin 2 for triggeringboth front and back sonar sensor.
  CalibrationFactor = 58.3; //Approx. around 58
  SonarSensor_Front_Back(CalibrationFactor);

}

void loop() {
  f1 = SonarSensor_Front_Back(pinB_4, pinF_2);
  delayMicroseconds(10);
  b1 = SonarSensor_Front_Back(pinB_4, pinB_2);


  Serial.print("f1: ");
  Serial.print(f1);
  Serial.print("   -   ");
  Serial.print("b1: ");
  Serial.println(b1);


}
