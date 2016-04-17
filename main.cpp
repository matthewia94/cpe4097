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
    StepperMotor s(4, 5, 6, 13);
	Actuator Gas(24,23);
	Actuator Brake(18,15);
	Gas.Set(1000,50,false);
    while(true)
    {
        //std::cin >> a;
		Gas.ActMove();
        s.step(-1);
    }
}
