#define Trigger 11
#define Echo 12

double Distance, Duration;

void setup() {
  Serial.begin(9600);
  pinMode(Trigger, OUTPUT);
  pinMode(Echo, INPUT);

}

void loop() {
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(5);                                      //trigger delay for reduced interference
  digitalWrite(Trigger, LOW);

  Duration = pulseIn(Echo, HIGH);                             //timeout is defualt 1 second add pulseIn(pin, HIGH/LOW, timeout) for specified time out
  Distance = (Duration / 58.3);

  Serial.println(Distance);

  delay(500);

}
