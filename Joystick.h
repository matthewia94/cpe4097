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

#define JOYSTICK_DEV "/dev/input/js0"

class Joystick
{
private:
    //Struct to store the state of a joystick
    struct joystick_state
    {
        std::vector<signed short> button;
        std::vector<signed short> axis;
    };

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
    joystick_state *joystick_st;
    __u32 version;
    __u8 axes;
    __u8 buttons;
    char name[256];

public:
    Joystick();
    ~Joystick();
    static void* loop(void* obj);
    void readEv();
    joystick_position joystickPosition(int n);
    bool buttonPressed(int n);
};


#endif //CPE4097_JOYSTICK_H
