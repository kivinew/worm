#pragma once
#include "header.h"
using namespace std;
class prize
{
    int             x, y, color;
    char            face;
    bool            state;
    time_t          lifeTime;
    static int      count;
public:
    prize()
    {
        srand((unsigned int) time(NULL));                            // -------------------------------------
        rand();
        x = rand() % 78;
        y = rand() % 23;
        color = rand() % 15;
        lifeTime = GetTickCount();
        face = ' ';
        state = true;
        count++;
    }

    ~prize()
    {
        lifeTime = (GetTickCount() - lifeTime) / 1000;
        cout << lifeTime;
    }

    void showPrize()
    {
        gotoXY(x, y, color);
        cout << face;
        return;
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

    static int getCount()
    {
        return count;
    }

    friend class worm;
};

int prize::count = 0;