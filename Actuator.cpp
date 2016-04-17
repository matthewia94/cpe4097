#include "Actuator.h"

Actuator::Actuator(int pwm_pin,int direc_pin)
{
	pwm = GPIOClass(std::to_string(pwm_pin));
	direc = GPIOClass(std::to_string(direc_pin));
	
	pwm.export_gpio();
    pwm.setdir_gpio("out");
	
	direc.export_gpio();
    direc.setdir_gpio("out");
}

Actuator::~Actuator()
{
	pwm.unexport_gpio();
	direc.unexport_gpio();
}

void Actuator::ActMove() //Moves actuator for one pulse
{
	pwm.setval_gpio("1");
	nanosleep(&tim1,&dn);
    pwm.setval_gpio("0");
	nanosleep(&tim2,&dn);
}

void Actuator::Set(int freq,int duty,bool direc)//PWM signal frequency, PWM signal duty cycle (0-100%), direction (false for cw, true for ccw) 
{
	float period = 1/freq;
	tim1.tv_sec = 0;
	tim2.tv_sec = 0;
	tim1.tv_nsec = (duty/100)*period*1000000000;
	tim2.tv_nsec = (1-(duty/100))*period*1000000000;
	if(direc == true)
		direc.setval_gpio("1");
	else
		direc.setval_gpio("0");
}