#include "mbed.h"
#include "INA219.hpp"
#include "SLCD.h"
#include "MAX17043.h"

// Get this to work with the INA219 Breakout from Adafruit
Serial pc(USBTX, USBRX);
INA219 ina219(D14, D15, 0x40, 400000, RES_10BITS);
MAX17043 max17043(D14, D15,0x6C);

int main()
{
    pc.baud(921600);
    SLCD slcd;
    float current_ma=0;
    float battery_percent=0;
    char text[10];

    slcd.clear();
    slcd.Home();
    slcd.printf("1.2.3.4");

    while (true) {
        wait(0.5);
        slcd.clear();
        slcd.Home();
        
        battery_percent = max17043.getFloatSOC(true);
        current_ma = ina219.read_current_mA();
        
        sprintf(text, "%2.2f", current_ma);
        slcd.printf("%s", text);
        pc.printf("Current: %s", text);
        
        wait(0.5);
        slcd.clear();
        slcd.Home();
        
        sprintf(text, "%2.2f", battery_percent);
        slcd.printf("%s", text);
        pc.printf("Battery: %s", text);
    }
}