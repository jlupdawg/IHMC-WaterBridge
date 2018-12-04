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
#define Pin2_1 7
#define Pin2_2 6
#define Pin4_2 11 //trigger pin for both Front and Back Sensors

double duration, distance_corner, distance_front_back, s1, s2, s3, s4, f1, b1;
double CalibrationFactor;

void setup() {
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
  CalibrationFactor = 58.3; //Approx. around 58
  SonarSensor_Front_Back(CalibrationFactor);

}

void loop() {
  f1 = SonarSensor_Front_Back(Pin4_2, Pin2_1);
  delayMicroseconds(10);
  b1 = SonarSensor_Front_Back(Pin4_2, Pin2_2);


  Serial.print("f1: ");
  Serial.print(f1);
  Serial.print("   -   ");
  Serial.print("b1: ");
  Serial.println(b1);

  
}
