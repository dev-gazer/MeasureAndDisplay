/**********************************************************************
* Filename    : I2CLCD1602.hpp
* Description : Use the LCD display data
* Author      : Alexandre Martuscelli Faria
*               (based on FreeNove Tutorials)
* modification: 30.06.2023
**********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <pcf8574.h>
#include <lcd.h>
#include <time.h>

#define BASE 64         // BASE any number above 64
//Define the output pins of the PCF8574, which are directly connected to the LCD1602 pin.
#define RS      BASE+0
#define RW      BASE+1
#define EN      BASE+2
#define LED     BASE+3
#define D4      BASE+4
#define D5      BASE+5
#define D6      BASE+6
#define D7      BASE+7

class I2CLCD1602{
    public:
        int pcf8574_address = 0x27;
        int lcdhd;
        int detectI2C(const int &addr);
};