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

    // Reset the motor controller
    reset.export_gpio();
    reset.setdir_gpio("out");
    reset.setval_gpio("0");
    sleep(1);
    reset.setval_gpio("1");
   
    // Initialize the clock pin
    clock.export_gpio();
    clock.setdir_gpio("out");
    clock.setval_gpio("1");
    
    // Initialize the ccw pin
    ccw.export_gpio();
    ccw.setdir_gpio("out");
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
    // Choose the direction for the motor
    if(num_steps < 0)
        ccw.setval_gpio("0");
    else
        ccw.setval_gpio("1");
    sleep(.001);
	
	/*// If we try to move the motor too far in the reverse direction,
	// motor will return to starting position
	if((offset + num_steps) < 0) 
	{
		num_steps = -offset;
		offset = 0;
	}	
	else
		offset += num_steps;
	
    // Step the correct number of times
    for(int i=0; i < abs(num_steps); i++)
    {
        clock.setval_gpio("0");
        sleep(1);
        clock.setval_gpio("1");
        sleep(1);
    }*/

}

void StepperMotor::run(int speed)
{
    if(speed > 0)
        ccw.setval_gpio("0");
    else
        ccw.setval_gpio("1");


    clock.setval_gpio("0");
    clock.setval_gpio("1");
}
