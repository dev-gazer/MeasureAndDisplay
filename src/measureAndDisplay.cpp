
/**********************************************************************
* Filename    : measureAndDisplay.cpp
* Description : Read the temperature and humidity data of DHT11
*               and display on the I2CLCD1602
* Author      : Alexandre Martuscelli Faria
*               (based on FreeNove Tutorials)
* modification: 30.06.2023
**********************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <pcf8574.h>
#include <lcd.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "DHTSensor/DHT.hpp"
#include "I2CLCD1602Display/I2CLCD1602.hpp"

#define DHT11_Pin  0		//define the pin of sensor

int main(){
    DHT dht;			//create a DHT class object
    int chk, counts;		//chk:read the return value of sensor; sumCnt:times of reading sensor
    I2CLCD1602 display;

    printf("Program is starting ...\n");

    wiringPiSetup();  
    if(display.detectI2C(0x27)){
        display.pcf8574_address = 0x27;
    }else if(display.detectI2C(0x3F)){
        display.pcf8574_address = 0x3F;
    }else{
        std::cout << "No correct I2C address found," << '\n';
        std::cout << "Please use command 'i2cdetect -y 1' to check the I2C address!" << '\n';
        std::cout << "Program Exit." << '\n';;
        return -1;
    }
    pcf8574Setup(BASE,display.pcf8574_address);//initialize PCF8574
    for(int i=0;i<8;i++){
        pinMode(BASE+i,OUTPUT);     //set PCF8574 port to output mode
    } 
    digitalWrite(LED,HIGH);     //turn on LCD backlight
    digitalWrite(RW,LOW);       //allow writing to LCD
	display.lcdhd = lcdInit(2,16,4,RS,EN,D4,D5,D6,D7,0,0,0,0);// initialize LCD and return “handle” used to handle LCD
    if(display.lcdhd == -1){
        std::cout << "lcdInit failed !" << '\n';
        return 1;
    }

    while (true){
        counts++; //counting number of reading times
        std::cout << "Measurement counts : " << counts << '\n';
        for (int i = 0; i < 15; i++){
            chk = dht.readDHT11(DHT11_Pin);	//read DHT11 and get a return value. Then determine whether data read is normal according to the return value.
            if(chk == DHTLIB_OK){
                std::cout << "DHT11,OK!" << '\n';
                break;
            }
            delay(100);
        }
        lcdPosition(display.lcdhd,0,1);
        lcdPrintf(display.lcdhd,"rF.: %.2f%%", dht.humidity);
        lcdPosition(display.lcdhd,0,0);
        lcdPrintf(display.lcdhd,"Temp.: %.2f C", dht.temperature);
        delay(2000);
    }
    return 1;
}
