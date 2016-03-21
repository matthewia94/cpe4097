/* 
 * File:   main.cpp
 * Author: Sam
 *         Matt 
 *
 * Created on February 10, 2016, 6:31 PM
 */

#include <iostream>
#include "StepperMotor.h"

int main ()
{
    int a;
    StepperMotor s(4, 5, 6, 13);
    while(true)
    {
        //std::cin >> a;
        s.step(-1);
    }
}
