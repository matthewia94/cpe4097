/* 
 * File:   main.cpp
 * Author: Sam
 *         Matt 
 *
 * Created on February 10, 2016, 6:31 PM
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "StepperMotor.h"
#include "client.h"
#include "Actuator.h"

using std::cout;
using std::endl;
using std::endl;

int main(int argc, char** argv)
{
    try
    {
        // Check command line arguments.
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_service io;
        Client c(io, argv[1], argv[2]);
        io.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    int a;
	double Freq = 50.0;
    StepperMotor s(4, 5, 6, 13);
	rpiPWM1 Stepper(300.0, 256, 0.0, rpiPWM1::MSMODE); //GPIO18, pin 12
    // initialize PWM1 output to 700Hz 8-bit resolution 0% Duty Cycle & PWM mode is MSMODE
	Actuator Gas(24,23);
	Actuator Brake(18,15);
	Gas.Set(false);
	Stepper.setDutyCycle(50.0);
    while(true)
    {
		Stepper.setFrequency(Freq++); //Increases frequency by one every 1/16 second
		usleep(62500);
		//Gas.ActMove();
		//std::cin >> a;
        //s.step(-1);
    }
}
