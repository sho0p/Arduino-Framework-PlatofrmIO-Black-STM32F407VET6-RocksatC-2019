#include <Arduino.h>
#include <SPI.h>
#include "adc.h"

SPIClass SPI_bus; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //SPI_bus.begin();
  SPI_bus = SPIClass(PIN_SPI_MOSI, PIN_SPI_MISO, PIN_SPI_SCK);

  pinMode(CS_PIN_1, OUTPUT);
  digitalWrite(CS_PIN_1, HIGH);
  
  SPI_bus.beginTransaction(CS_PIN_1, SPISettings(1000000, MSBFIRST, SPI_MODE0));
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t bothCh = readAdc(CS_PIN_1);
  printData(bothCh);
  Serial.print(MOSI_PIN);
  Serial.print(" ");
  Serial.print(MISO_PIN);
  Serial.print(" ");
  Serial.println(SCK_PIN);
}

void printData(uint32_t chData){
  Serial.print(chData >> 16);
  Serial.print(" ");
  Serial.println(chData & 0x03FF);
}

uint32_t readAdc(int csPin){
  uint32_t data;
  uint16_t regData = SETUP_FLAG | 1 << 3 | SCAN_MODE_0_N;
//  digitalWrite(csPin,LOW);

  uint16_t msb = SPI_bus.transfer16(regData);
  uint16_t lsb = SPI_bus.transfer16(0x00);

  data = (msb << 6 | lsb >> 2);
  data <<= 16;

  msb =  SPI_bus.transfer16(0x00);
  lsb =  SPI_bus.transfer16(0x00);

  data |= (msb <<6 | lsb>>2);
  //digitalWrite(csPin, HIGH);
  return data;
}