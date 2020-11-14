#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  //delay(10000);
}
void loop() {
//  NRFpinMode(0,4,OUTPUT);
//  NRFpinMode(0,5,OUTPUT);
//  NRFdigitalWrite(0,4,LOW);
//  NRFdigitalWrite(0,5,HIGH);
//  NRFpinMode(1,4,OUTPUT);
//  NRFpinMode(1,5,OUTPUT);
//  NRFdigitalWrite(1,4,LOW);
//  NRFdigitalWrite(1,5,LOW);
//  delay(1000);
//  NRFdigitalWrite(1,5,HIGH);
//  NRFdigitalWrite(0,5,LOW);
//  delay(1000);
//
//  int value = analogRead(A0);
//  int angle = value / 63;
//  NRFservoMotor(1, 9, angle);
  //delay(1);
//
  NRFstepperMotor(1, 8);
}

void NRFpinMode(byte device, byte pin, byte val)
{
  const byte data[] = {device, 0, pin, val};
  radio.write(&data, sizeof(data));
}

void NRFdigitalWrite(byte device, byte pin, byte val)
{
  const byte data[] = {device, 1, pin, val};
  radio.write(&data, sizeof(data));
}

void NRFservoMotor(byte device, byte pin, byte val)
{
  const byte data[] = {device, 2, pin, val};
  radio.write(&data, sizeof(data));
}

void NRFstepperMotor(byte device, byte val)
{
  const byte data[] = {device, 3, 0, val)
  radio.write(&data, sizeof(data));
}
