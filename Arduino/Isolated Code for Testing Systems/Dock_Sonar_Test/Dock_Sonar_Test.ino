#define trigPin_1 13
#define echoPin_1 4
#define trigPin_2 10
#define echoPin_2 9

 
long duration, distance, s1, s2;
 
void setup(){
Serial.begin (9600);
pinMode(trigPin_1, OUTPUT);
pinMode(echoPin_1, INPUT);
pinMode(trigPin_2, OUTPUT);
pinMode(echoPin_2, INPUT);

}
 
void loop(){
SonarSensor(trigPin_1, echoPin_1);
s1 = distance;
SonarSensor(trigPin_2, echoPin_2);
s2 = distance;
 
Serial.print("s1: ");
Serial.print(s1);
Serial.print(" - ");
Serial.print("s2: ");
Serial.print(s2);

delay(100);
}
 
void SonarSensor(int trigPin,int echoPin){
digitalWrite(trigPin, HIGH);
delayMicroseconds(12);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = (duration) / 58.3;
}
