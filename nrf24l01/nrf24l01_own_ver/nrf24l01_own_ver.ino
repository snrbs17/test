//pin number define
#include<SPI.h>
#define CE_pin 7
#define CSN_pin 8
#define MOSI_pin 51
#define MISO_pin 50
#define SCK_pin 52

//byte registerCtrl[5];//, registerCtrlSub2, registerCtrlSub3
byte command, registerAddress, registerBit, pinNumber, transmitValue;
byte data_in[5];
byte* modeSelect(
enum mode {NRFpinMode, NRFpinWrite, datacheck, NRFpinRead, pingTransmit}

void setup() {

  Serial.begin(115200);
  Serial.println("Serial begin");
  delay(100);
  NRFinit();
  NRFsetRXpayload(0,3); //pipe 0, byte size 3
  NRFgetRegister(7); //7:STATUS register, 1: show detail in screen
  NRFreviseRegisterBit(0,0,1);
  NRFreviseRegisterBit(0,1,1);
  NRFreviseRegisterBit(0,4,1);
  NRFreviseRegisterBit(0,5,1); //settings for turning off the interrupt for some factors
  //interrupt occurs only when RX_DR(=Receive Data Ready) asserts

  digitalWrite(CSN_pin, LOW);
  command = SPI.transfer(B11100010);//flush RX
  digitalWrite(CSN_pin, HIGH);

  digitalWrite(CSN_pin, LOW);
  command = SPI.transfer(B11100001);//flush TX
  digitalWrite(CSN_pin, HIGH);

  NRFclearInterrupts();//clears any interrupts
  delay(100);
  attachInterrupt(0, get_data, FALLING);//0 for this function points pin 2

  NRFpinMode(3, 0); //pin number3 of receiver INPUT mode
  //NRFpinWrite(3, 1);//pin number3 of receiver HIGH
}

void loop() {
  if(NRFpinRead(3)==0){
    NRFpinMode(7,1);
    NRFpinWrite(7,1);
    delay(100);
    NRFpinWrite(7,0);
    delay(100);
  }
}

void NRFsetRXpayload(byte pipe, byte bytes)
{
  byte command
}

void NRFclearInterrupts()
{
  for(int i = 4; i <=6; i ++)
  {
    NRFgetAddress(7, 0);
    if(bitRead(registerBit, i))
      NRFreviseRegisterBit(7,i,1);
  }
}

void NRFgetAddress(byte address)//, byte info)
{
  digitalWrite(CSN_pin, LOW);
  command = SPI.transfer(address);
  registerBit = SPI.transfer(B00000000);
  digitalWrite(CSN_pin, HIGH);
}

void NRFreviseRegisterBit(byte address, byte bitAddress, byte val)
{
  NRFgetAddress(address);
  if(val)//val ==1 || 0
    bitSet(registerBit, bitAddress);
  else
    bitClear(registerBit, bitAddress);

    digitalWrite(CSN_pin, LOW);
    command = SPI.transfer(32+address);//write register
    registerBit = SPI.transfer(registerBit);
    digitalWrite(CSN_pin, HIGH);
}

void transmit(byte mode, byte pin, byte value){
  digitalWrite(CSN_pin, LOW);
  command = SPI.transfer(B11100001);//flush TX
  digitalWrite(CSN_pin, HIGH);

  digitalWrite(CSN_pin, LOW);
  command = SPI.transfer(B10100000);//load TX payload
  
}
