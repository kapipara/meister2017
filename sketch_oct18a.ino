#include <SPI.h>

#define PIN_BUSY 9
#define PIN_SDO 12 /* SPIデータ出力 */
#define PIN_SDI 11 /* SPIデータ入力 */
#define PIN_SS 8

void L6470_send(unsigned char sendData);
void L6470_resetDevice(); 
void L6470_constRun();

void setup(){
  SPI.begin();
  SPI.setBitOrder( MSBFIRST );
  SPI.setDataMode( SPI_MODE3 );
}

void loop(){
   L6470_constRun();
}

void L6470_resetDevice(){
  /* 命令実行中にリセットするのを避けるため空命令を4回くらい送っとく */
  /* 0x00はNOP(Nothing is performed)命令らしい */
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);
  L6470_send(0x00);
  /* Reset信号 */
  L6470_send(0xc0);
}

void L6470_send(unsigned char sendData){
  while(!digitalRead(PIN_BUSY)){ }
  digitalWrite(PIN_SS,LOW);
  SPI.transfer(sendData);
  digitalWrite(PIN_SS,HIGH);
}

void L6470_constRun(){
  L6470_send(0x51);
  L6470_send(0x0a);
  L6470_send(0x0a);
  L6470_send(0x0a);
}

