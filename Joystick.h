//
// Created by matt on 2/8/16.
// Based off of the code found at: http://www.keithlantz.net/2011/10/a-linux-c-joystick-object/
//

#ifndef CPE4097_JOYSTICK_H
#define CPE4097_JOYSTICK_H

#include <unistd.h>
#include <vector>
#include <pthread.h>
#include <iostream>
#include <cmath>
#include <linux/joystick.h>
#include <fcntl.h>
#include <boost/serialization/vector.hpp>

#define JOYSTICK_DEV "/dev/input/js0"

class Joystick
{
    private:
        //State to store the position of the actual analog sticks
        struct joystick_position
        {
            float theta;
            float r;
            float x;
            float y;
        };

        pthread_t thread;
        bool active;
        int joystick_fd;
        js_event* joystick_ev;
        __u32 version;

        char name[256];

    public:
        //Struct to store the state of a joystick
        struct joystick_state
        {
            friend class boost::serialization::access;
            int num_buttons, num_axes;
            std::vector<signed short> button;
            std::vector<signed short> axis;

            template <typename Archive>
            void serialize(Archive& ar, const unsigned int version)
            {
                ar & num_axes;
                ar & axis;
                ar & num_buttons;
                ar & button;
            }
        };

        __u8 axes;
        __u8 buttons;
        joystick_state joystick_st;

        Joystick();
        ~Joystick();
        static void* loop(void* obj);
        void readEv();
        joystick_position joystickPosition(int n);
        bool buttonPressed(int n);
};


#endif //CPE4097_JOYSTICK_H
