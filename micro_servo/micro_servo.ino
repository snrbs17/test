void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
}

void loop() {
  int value = analogRead(A0);
  int angle = value *2 +352;
  delay(1);
  
  //if(Serial.available()>0)
  //{

    Serial.println(angle);
    //delay(500);
  

    for (int i =0; i < 20; i++)
    {
      digitalWrite(9, HIGH);
      delayMicroseconds(angle);
      digitalWrite(9, LOW);
      delayMicroseconds(2400-angle);
    }
  //}
}
