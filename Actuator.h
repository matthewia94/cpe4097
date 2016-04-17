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
		void ActMove();
		void Set(int freq,int duty,bool direc);
	private:
		GPIOClass pwm; //GPIO pwm pin, signal input
		GPIOClass direc; //GPIO direction pin, low for CW motion, high for CCW motion
		struct timespec tim1; //PWM On time
		struct timespec tim2; //PWM Off time
		struct timespec dn; //Dummy
};

#endif