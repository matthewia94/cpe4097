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

void Actuator::ActMove() //Moves actuator
{
	pwm.setval_gpio("1");
}

void Actuator::ActStop() //Stops actuator
{
	pwm.setval_gpio("0");
}

void Actuator::Set(bool direct)//direction (false for cw, true for ccw) 
{
	if(direct == true)
		direc.setval_gpio("1");
	else
		direc.setval_gpio("0");
}