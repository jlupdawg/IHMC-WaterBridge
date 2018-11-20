byte ESC = 8;

void setup() {
  pinMode(ESC, OUTPUT);
  analogWrite(ESC, 0);
  delay(3000);
}

void loop() {
  for(int i = 0; i< 256; i++){
  analogWrite(ESC,i);
  delay(25);
  }
}
