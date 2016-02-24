/**
 * @file StepperMotor.h
 * @brief A class to control a stepper motor on the raspberry pi
 * @author Matt Anderson <mia2n4@mst.edu>
 */

#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <unistd.h>
#include "GPIOClass.h"

class StepperMotor
{
    public:
        StepperMotor(int clock_pin, int ccw_pin, int reset_pin, int en_pin);
        void step(int num_steps);

    private:
       int offset; 
       GPIOClass clock, ccw, reset, en;
};

#endif
