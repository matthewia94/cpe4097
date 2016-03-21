/**
 * @file StepperMotor.h
 * @brief A class to control a stepper motor on the raspberry pi
 * @author Matt Anderson <mia2n4@mst.edu>
 */

#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include "GPIOClass.h"

class StepperMotor
{
    public:
        StepperMotor(int clock_pin, int ccw_pin, int reset_pin, int en_pin);
        ~StepperMotor();
        void step(int num_steps);

    private:
        int offset;         // The offset of the stepper motor from 0, 0 is the starting position 
        GPIOClass clock;    // The clock pin is used to make the motor step once
        GPIOClass ccw;      // The ccw pin sets the direction of the motor 
        GPIOClass reset;    // The reset pin resets the Motor driver IC
        GPIOClass en;       // The en pin allows the controller to accept commands
};

#endif
