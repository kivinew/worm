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
    prize(): x ( rand() % 78), y ( rand() % 23), color (rand() % 15)
    {
        lifeTime = GetTickCount();
        face = ' ';
        state = true;
        count++;
    }

    ~prize() {    }
    // вывод приза
    void showPrize()
    {
        gotoXY(x, y, color);
        cout << face;
        return;
    }
    // цвет приза
    int getColor()
    {
        return color;
    }
    // установить активность приза
    void setState(bool change)
    {
        if (GetTickCount() - lifeTime > 1000)
            state = false;
        else
            state = true;
        if (change) state = true;
        else state = false;
        return;
    }
    // активность приза
    int getState()
    {
        return state;
    }
    // количество призов
    static int getCount()
    {
        return count;
    }

    friend class worm;
};

int prize::count = 0;