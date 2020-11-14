int lookup[8]={B01000, B01100, B00100, B00110, B00010, B00011, B0001, B01001};
int stepperPin[4] = {9, 10, 11, 12};
void setup() {
  Serial.begin(9600);
  
//  for (int i = 9; i<=12; i++)
//  {
//    pinMode(i, OUTPUT);
//  }

}

void loop() {
//  for(int i=0; i<8; i++)
//  {
//    for (int j = 0; j<4; j++)
//    {
//      digitalWrite(9+j, bitRead(lookup[8-i],j));
//    }
//    delayMicroseconds(1200);
      int val = 8;
      int directionVal;
      int speedVal = val<0? 9+val : 9-val;

      for (int k = 0; k<4; k++)
      {
        pinMode(stepperPin[k], OUTPUT);
      }
      for (int i=0; i<8; i++)
      {
        for (int j =0; j<4; j++)
        {
          directionVal = val<0?8-i:i;
          digitalWrite(stepperPin[j], bitRead(lookup[directionVal],j));
        }
        delayMicroseconds(1200*speedVal);
      }
//  }
}
