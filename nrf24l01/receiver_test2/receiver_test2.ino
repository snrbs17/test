#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

#define deviceId 1
enum modeSelect {_pinMode, _digitalWrite, servoMotor, stepperMotor};

int lookup[8]={B01000, B01100, B00100, B00110, B00010, B00011, B0001, B01001};
int stepperPin[4] = {3, 4, 6, 10};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {
  if (radio.available()) {
    byte data[4] = {0,};
    radio.read(&data, sizeof(data));
    byte device = data[0];
    byte mode = data[1];
    byte pin = data[2];
    byte val = data[3];
    if(device == deviceId)
    {
      if (mode == _pinMode)
      {
        Serial.print("pinMode(");
        Serial.print(pin);
        Serial.print(",");
        Serial.print(val);
        Serial.println(")");
        
        pinMode(pin, val);
      }
      
      if (mode == _digitalWrite)
      {
        Serial.print("digitalWrite(");
        Serial.print(pin);
        Serial.print(",");
        Serial.print(val);
        Serial.println(")");
        
        digitalWrite(pin, val);
      }
      
      if (mode == servoMotor)
      {
        pinMode(pin, OUTPUT);
        for (int i = 0; i <20; i++)
        {
          digitalWrite(pin, HIGH);
          delayMicroseconds(400 + (val * 125));
          digitalWrite(pin, LOW);
          delayMicroseconds(2400 - (val * 125));
        }
      }

      if (mode == stepperMotor)
      {
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
      }
    }
  }
}
