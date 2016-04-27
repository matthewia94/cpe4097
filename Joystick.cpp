//
// Created by matt on 2/8/16.
//

#include "Joystick.h"

Joystick::Joystick()
{
    active = false;
    joystick_fd = 0;
    joystick_ev = new js_event();
    joystick_fd = open(JOYSTICK_DEV, O_RDONLY | O_NONBLOCK);
    if(joystick_fd > 0)
    {
        ioctl(joystick_fd, JSIOCGNAME(256), name);
        ioctl(joystick_fd, JSIOCGVERSION, &version);
        ioctl(joystick_fd, JSIOCGAXES, &axes);
        ioctl(joystick_fd, JSIOCGBUTTONS, &buttons);

        joystick_st.axis.reserve(axes);
    }
    joystick_st.num_buttons = buttons;
    joystick_st.num_axes = axes;
    for(int i = 0; i < axes; i++)
    {
        joystick_st.axis.push_back(0);
    }
    for(int i = 0; i < buttons; i++)
    {
        joystick_st.button.push_back(0);
    }
    active = true;
    pthread_create(&thread, 0, &Joystick::loop, this);
}

Joystick::~Joystick()
{
    if(joystick_fd > 0)
    {
        active = false;
        pthread_join(thread, 0);
        close(joystick_fd);
    }

    delete joystick_ev;
    joystick_fd = 0;
}

void* Joystick::loop(void *obj)
{
    while(reinterpret_cast<Joystick*>(obj)->active)
    {
        reinterpret_cast<Joystick *>(obj)->readEv();
    }
}

void Joystick::readEv()
{
    int bytes = read(joystick_fd, joystick_ev, sizeof(*joystick_ev));
    if (bytes > 0)
    {
        joystick_ev->type &= ~JS_EVENT_INIT;
        if(joystick_ev->type & JS_EVENT_BUTTON)
        {
            joystick_st.button[joystick_ev->number] = joystick_ev->value;
        }
        if(joystick_ev->type & JS_EVENT_AXIS)
        {
            joystick_st.axis[joystick_ev->number] = joystick_ev->value;
        }
    }
}

bool Joystick::buttonPressed(int n)
{
    return n > -1 && n < buttons ? joystick_st.button[n] : 0;
}

Joystick::joystick_position Joystick::joystickPosition(int n)
{
    joystick_position pos;

    if(n > -1 && n < buttons)
    {
        int i0 = n*2, i1 = n*2+1;
        float x0 = joystick_st.axis[10]/32767.0f, y0 = -joystick_st.axis[i1]/32767.0f;
        float x = x0 * sqrt(1 - pow(y0, 2)/2.0f), y = y0 * sqrt(1 - pow(x0, 2)/2.0f);

        pos.x = x0;
        pos.y = y0;

        pos.theta = atan2(y, x);
        pos.r = sqrt(pow(y, 2) + pow(x, 2));
    }
    else
    {
        pos.theta = pos.r = pos.x = pos.y = 0.0f;
    }

    return pos;
}