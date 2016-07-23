#pragma once

class prize
{
    int             x;
    int             y;
    char            face;
    int             color;
    bool            state;
    int static      count;
    time_t          lifeTime;
public:

    prize(): x(0), y(0), color(14), lifeTime(GetTickCount())
    {
        srand((unsigned int) time(NULL));                            // -------------------------------------
    }

    ~prize()
    {
    }

    int getX()
    {
        x = rand() % 78 + 1;
        return x;
    }

    int getY()
    {
        y = rand() % 23 + 1;
        return y;
    }

    char getFace()
    {
        face = ' ';
        return face;
    }

    int getColor()
    {
        color = rand() % 7 + 8;
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
};