/**
 * @file StepperMotor.cpp
 * @brief The class implementation file for StepperMotor
 * @author Matt Anderson <mia2n4@mst.edu>
 */

#include "StepperMotor.h"

StepperMotor::StepperMotor(int clock_pin, int ccw_pin, int reset_pin, int en_pin)
{
    clock = GPIOClass(std::to_string(clock_pin));
    ccw = GPIOClass(std::to_string(ccw_pin));
    reset = GPIOClass(std::to_string(reset_pin));
    en = GPIOClass(std::to_string(en_pin));

    offset = 0;

    // Turn on enable pin
    en.export_gpio();
    en.setdir_gpio("out");
    en.setval_gpio("1");

    reset.export_gpio();
    reset.setdir_gpio("out");
    reset.setval_gpio("1");
    sleep(1);
    reset.setval_gpio("0");
    
    clock.export_gpio();
    clock.setdir_gpio("out");
    
    ccw.export_gpio();
    clock.setdir_gpio("out");
}

StepperMotor::~StepperMotor()
{
	clock.unexport_gpio();
	ccw.unexport_gpio();
	reset.unexport_gpio();
	en.unexport_gpio();
}

void StepperMotor::step(int num_steps)
{
    for(int i=0; i < num_steps; i++)
    {
        clock.setval_gpio("1");
        sleep(5);
        clock.setval_gpio("0");
        sleep(1);
    }
    offset += num_steps;
}
