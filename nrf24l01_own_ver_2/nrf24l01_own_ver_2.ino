//pin number define
#include<SPI.h>
#define CE_pin 7
#define CSN_pin 8
#define MOSI_pin 51
#define MISO_pin 50
#define SCK_pin 52
#define IRQ_pin 2

#define flush_RX B11100010
#define flush_TX B11100001
#define byteReading SPI.transfer(B00000000)

byte data_in[5];//0:status register, 1~:data

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
  data_in[0] = SPI.transfer(flush_RX);
  digitalWrite(CSN_pin, HIGH);

  digitalWrite(CSN_pin, LOW);
  command = SPI.transfer(flush_TX);
  digitalWrite(CSN_pin, HIGH);

  NRFclearInterrupts();
  delay(100);
  attachInterrupt(0, get_data, FALLING);

  NRFpinMode(3,0);
  NRFpinWrite(3,1);
}

void loop(){
  if(NRFpinRead(3)==0){
    NRFpinMode(7,1);
    NRFpinWrite(7,1);
    delay(100);
    NRFpinWrite(7,0);
    delay(100);
  }
}

void NRF_Init(){//  start NRF init  start NRF init  start NRF init  start NRF init  start NRF init
  
  pinMode(CE_pin, OUTPUT);//chip enable set as output
  pinMode(CSN_pin, OUTPUT);//chip select pin as output
  pinMode(MOSI_pin, OUTPUT);//SPI data out
  pinMode(MISO_pin, INPUT); //SPI data in
  pinMode(SCK_pin, OUTPUT);//SPI clock out
  Serial.println("NRF Pins Initialized");
  SPI.setBitOrder(MSBFIRST);//SPI Most Significant Bit First
  SPI.setDataMode(SPI_MODE0);// Mode 0 Rising edge of data, keep clock low
  SPI.setClockDivider(SPI_CLOCK_DIV4);//Run the data in at 16MHz/2 - 8MHz
  digitalWrite(CE_pin, HIGH);//RX mode
  digitalWrite(CSN_pin, HIGH);//SPI idle
  SPI.begin();//start up the SPI library
  Serial.println("NRF Ready");
}

void NRFsetRXpayload(byte pipeNo, byte sizeOfData)
{
  byte selectPipeToWrite = 32 + 17 + pipeNo;
  digitalWrite(CSN_pin, LOW);
  data_in[0] = SPI.transfer(selectPipeToWrite);
  data_in[1] = SPI.transfer(sizeOfData);
  digitalWrite(CSN_pin, HIGH);
}

void NRFgetRegister(byte registerAddress)
{
  readTheRegister = 0 + registerAddress;
  digitalWrite(CSN_pin, LOW);
  data_in[0] = SPI.transfer(readTheRegister);
  data_in[1] = byteReading;
  digitalWrite(CSN_pin, HIGH);
}

void NRFclearInterrupts()
{
  for (int i =4; i <=6; i ++)
  {
    NRFgetAddress(7,0);
    if(bitRead(registerBit,i))
      NRFreviseRegisterBit(7,i,1);
  }
}

void NRFreviseRegisterBit(byte registerAddress, byte registerBit, byte value)
{
  NRFgetRegister(registerAddress);
  if(value ==1)
    bitSet(data_in[1], registerBit);
  else
    bitClear(data_in[1], registerBit);

  digitalWrite(CSN_pin, LOW);
  data_in[0] = SPI.transfer(32+address);
  data_in[1] = SPI.transfer(data_in[1]);
  digitalWrite(CSN_pin, HIGH);
}

  
