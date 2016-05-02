//
// Created by matt on 4/27/16.
//

#include "Lawnmower.h"

Lawnmower::Lawnmower() : s(18, 23, 24, 25), gas(22, 27), brake(17, 4), stop_relay("12")
{
    stop_relay.export_gpio();
    stop_relay.setdir_gpio("out");
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
        stop_relay.setval_gpio("1");
	sleep(.05);
    }

    if(enabled)
    {
        if(js.axis[0] < -10000)
        {
            s.step(-100);
        }
        else if(js.axis[0] > 10000)
        {
            s.step(100);
        }
	if(js.button[5])
	{
            gas.set(1);
            gas.actMove();
	}
        else if(js.axis[5] > 500)
        {
	    gas.set(0);
            gas.actMove();
        }
        else
        {
            gas.actStop();
        }
	if(js.button[4])
	{
            brake.set(1);
            brake.actMove();
	}
        else if(js.axis[2] > 500)
        {
	    brake.set(0);
            brake.actMove();
        } 
        else
        {
            brake.actStop();
        }
    }
    else
    {
        e_stop();
    }
}

void Lawnmower::e_stop()
{
    // Emergency stop
    stop_relay.setval_gpio("0");
    sleep(.05);
}
