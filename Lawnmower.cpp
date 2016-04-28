//
// Created by matt on 4/27/16.
//

#include "Lawnmower.h"

Lawnmower::Lawnmower() : s(4, 5, 6, 13), gas(23, 18), brake(24, 25)
{
    rpiPWM1 Stepper(300.0, 256, 0.0, rpiPWM1::MSMODE); //GPIO18, pin 12
    Stepper.setDutyCycle(50.0);
    enabled = false;
}

void Lawnmower::update_state(Joystick::joystick_state js)
{
    if(js.button[1])  // B turns off
    {
        enabled = false;
        e_stop();
    }
    else if(js.button[0])  // A turns on
    {
        enabled = true;
    }

    if(enabled)
    {
        if(js.axis[0] < -10000)
        {
            s.step(-50);
        }
        else if(js.axis[0] > 10000)
        {
            s.step(50);
        }
        if(js.axis[5] > 0)
        {
            gas.actMove();
        }
        else
        {
            gas.actStop();
        }
        if(js.axis[2] > 0)
        {
            brake.actMove();
        }
        else
        {
            brake.actStop();
        }
    }
    else
    {

    }
}

void Lawnmower::e_stop()
{
    // Emergency stop
}