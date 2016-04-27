#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <stdio.h>
#include <time.h>
#include "GPIOClass.h"

class Actuator
{
	public:
		Actuator(int pwm_pin,int direc_pin); //Constructor
		~Actuator(); //Destructor
		void ActMove(); //Moves actuator by outputting 3.3 V to GPIO PWM pin
		void ActStop(); //Stops actuator by setting GPIO PWM pin to 0 V
		void Set(bool direct); //Changes direction pin to 0 V for cw motion or 3.3 V for ccw motion
	private:
		GPIOClass pwm; //GPIO pwm pin, signal input
		GPIOClass direc; //GPIO direction pin, low for CW motion, high for CCW motion
};

#endif