#define trigPin_1 39
#define echoPin_1 41
#define trigPin_2 21
#define echoPin_2 23
#define trigPin_3 25
#define echoPin_3 27
#define trigPin_4 37
#define echoPin_4 35

 
long duration, distance, s1, s2, s3 ,s4;
 
void setup(){
Serial.begin (115600);
pinMode(trigPin_1, OUTPUT);
pinMode(echoPin_1, INPUT);
pinMode(trigPin_2, OUTPUT);
pinMode(echoPin_2, INPUT);

pinMode(trigPin_3, OUTPUT);
pinMode(echoPin_3, INPUT);
pinMode(trigPin_4, OUTPUT);
pinMode(echoPin_4, INPUT);
}
 
void loop(){
SonarSensor(trigPin_1, echoPin_1);
s1 = distance;
SonarSensor(trigPin_2, echoPin_2);
s2 = distance;

SonarSensor(trigPin_3, echoPin_3);
s3 = distance;
SonarSensor(trigPin_4, echoPin_4);
s4 = distance;
 
Serial.print("s1: ");
Serial.print(s1);
Serial.print(" - ");
Serial.print("s2: ");
Serial.print(s2);
Serial.print("s3: ");
Serial.print(s3);
Serial.print(" - ");
Serial.print("s4: ");
Serial.print(s4);
Serial.println();

delay(100);
}
 
void SonarSensor(int trigPin,int echoPin){
digitalWrite(trigPin, HIGH);
delayMicroseconds(12);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);

duration = pulseIn(echoPin, HIGH);
distance = (duration) / 58.3;
}
