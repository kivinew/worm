#pragma once
#include "header.h"
using namespace std;
class prize
{
    int             x, y, color;
    char            face;
    bool            state;
    time_t          birth;
    time_t          lifeTime;
    bool            tempEffect;
    static int      count;
public:
    prize(): x(rand() % 77 + 1), y(rand() % 22 + 1), color(rand() % 15)
    {
        if (color == LightRed)
            lifeTime = (time_t) rand() % 3 + 8;
        if (color == Green)
            lifeTime = (time_t) rand() % 3 + 1;
        birth = GetTickCount();
        face = ' ';
        state = true;
        count++;
        _getch();
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
        state = change;
        return;
    }
    // активность приза
    bool getState()
    {
        if ((GetTickCount() - birth) / 1000 > lifeTime)
            state = false;
        else
            state = true;
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