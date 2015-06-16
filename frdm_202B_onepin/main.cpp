#include "mbed.h"
#include "SLCD.h"

SLCD slcd;
AnalogOut DAC(PTE30);
Serial pc(USBTX, USBRX);
AnalogIn Ain1(PTB0);
//AnalogIn Ain2(PTB1);

int main() 
{
    float ADCdata1;
    //float ADCdata2;
    float high_out = 0.999;
    float low_out = 0.0;
    float current_out = low_out;
    slcd.clear();
    int state = 0;
    while (1) {
        ADCdata1=Ain1*3.3;
        //ADCdata2=Ain2*3.3;
        pc.printf("recv_in_1 %f \n\r",ADCdata1);
        //pc.printf("recv_in_2 %f \n\r",ADCdata2);
        pc.printf("state %i \n\r",state);
        pc.printf("output %f \n\r", current_out);        
        wait (0.2);
        //3.8 -> 0.95
        if (state == 0 && ADCdata1 < 0.95)
        {current_out = high_out;
            state = 1;}                
        //7.5 -> 1.785
        //7 -> 1.75
        if (state == 1 && ADCdata1 > 1.785)
        {current_out = low_out;
            state = 0;}            
        DAC = current_out;
        slcd.printf("%1.3f", ADCdata1);
    }
}