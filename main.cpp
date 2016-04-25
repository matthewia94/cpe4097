/* 
 * File:   main.cpp
 * Author: Sam
 *         Matt 
 *
 * Created on February 10, 2016, 6:31 PM
 */

#include <iostream>
#include "StepperMotor.h"
#include "Actuator.h"

int main ()
{
    int a;
	double Freq = 50.0;
    StepperMotor s(4, 5, 6, 13);
	rpiPWM1 Stepper(300.0, 256, 0.0, rpiPWM1::MSMODE); //GPIO18, pin 12
    // initialize PWM1 output to 700Hz 8-bit resolution 0% Duty Cycle & PWM mode is MSMODE
	Actuator Gas(24,23);
	Actuator Brake(18,15);
	Gas.Set(false);
	Stepper.setDutyCycle(50.0);
    while(true)
    {
		Stepper.setFrequency(Freq++); //Increases frequency by one every 1/16 second
		usleep(62500);
		//Gas.ActMove();
		//std::cin >> a;
        //s.step(-1);
    }
}
