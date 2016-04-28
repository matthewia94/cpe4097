//
// Created by matt on 4/27/16.
//

#ifndef CPE4097_LAWNMOWER_H
#define CPE4097_LAWNMOWER_H

#include "StepperMotor.h"
#include "Actuator.h"
#include "rpiPWM1.h"
#include "Joystick.h"

class Lawnmower
{
    private:
        StepperMotor s;
        Actuator gas;
        Actuator brake;
        bool enabled;

    public:
        Lawnmower();
        void update_state(Joystick::joystick_state js);
        void e_stop();
};


#endif //CPE4097_LAWNMOWER_H
