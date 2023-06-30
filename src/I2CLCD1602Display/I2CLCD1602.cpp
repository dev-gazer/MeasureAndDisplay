/**********************************************************************
* Filename    : I2CLCD1602.cpp
* Description : Use the LCD display data
* Author      : Alexandre Martuscelli Faria
*               (based on FreeNove Tutorials)
* modification: 30.06.2023
**********************************************************************/
#include "I2CLCD1602.hpp"

int I2CLCD1602::detectI2C(const int &addr){
    int _fd = wiringPiI2CSetup (addr);   
    if (_fd < 0){
        return 0 ;
    } 
    else{	
        if(wiringPiI2CWrite(_fd,0) < 0){
            return 0;
        }
        else{
            return 1 ;
        }
    }
}