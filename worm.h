#pragma once
#include <iostream>
#include "goto.h"
using namespace std;

class worm
{
    int length,
        life,
        direction;                                                          // направление движения;
    static int **ip_worm;                                                   // указатель на динамический массив

public:
    static worm& getWorm()
    {
        static worm object;
        return object;
    }

    int getLenght()
    {
        return length;
    }

    void increase()
    {
        if (length < 40)
            length++;
        else
        {
            life++;
            length = 3;
        }
    }

    void decrease()
    {
        if (length > 3)
            length--;
        else
            exit(0);
    }

    void setDirection(int dir)
    {
        direction = dir;
    }

    int getDirection()
    {
        return direction;
    }

    int getX()
    {
        return ip_worm[0][0];
    }
    
    int getY()
    {
        return ip_worm[0][1];
    }

    void shift()
    {
        int dX, dY;
        if (direction == 0) dX = -1;
        if (direction == 1) dX = 1;
        if (direction == 2) dY = -1;
        else dY = 1;
        ip_worm[0][0] += dX;                                              // 
        ip_worm[0][1] += dY;                                              // прибавляем смещение



        for (int i = length - 1; i > 0; i--)                                /* сдвигаем элементы массива на один вправо         */
        {                                                                   /*                                                  */
            ip_worm[i][0] = ip_worm[i - 1][0];                              /*                                                  */
            ip_worm[i][1] = ip_worm[i - 1][1];                              /*                                                  */
        }
    }

    void show(int color)                                                    // вывод червя
    {
        int tailX, tailY, i;                                                // хвостовой элемент, затирающий след
        for (i = 0; i < length; i++)
        {
            gotoXY(ip_worm[i][0], ip_worm[i][1], color);
            cout << " ";
        }
        tailX = ip_worm[i][0];
        tailY = ip_worm[i][1];
        gotoXY(tailX, tailY, 15);
        cout << " ";
        return;
    }

private:
    worm():length(3), direction(1)
    {    }

    ~worm()
    {    }

    worm(const worm&) = delete;
    worm& operator=(const worm&) = delete;
};

