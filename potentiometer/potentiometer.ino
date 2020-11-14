void setup() {
  Serial.begin(9600);
  
}

void loop() {
  //if(Serial.available()>0)
  
  int value = analogRead(A0);
  int angle = value *2 +352;
  Serial.println(angle);
  //delay(500);
  
}
