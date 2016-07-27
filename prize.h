#pragma once
#include "header.h"
class prize
{
    int             x;
    int             y;
    char            face;
    int             color;
    bool            state;
    int             count;
    time_t          lifeTime;
public:

    prize()
    {
        srand((unsigned int) time(NULL));                            // -------------------------------------
        x = rand() % 78;
        y = rand() % 23;
        color = LightBlue;
        lifeTime = GetTickCount();
        count = 1;
        face = ' ';
        state = true;
    }

    ~prize(){    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    char getFace()
    {
        return face;
    }

    int getColor()
    {
        return color;
    }

    void setState()
    {
        if (GetTickCount() - lifeTime > 1000)
            state = 0;
        else
            state = 1;
    }

    int getState()
    {
        return state;
    }

    int getCount()
    {
        return count;
    }
};