#pragma once
#include <iostream>
using namespace std;

class worm
{
    int lenght;
    static int **ip_worm;                                               // указатель на динамический массив
    int direction;                                               // направление движения

public:
    static worm& getWorm()
    {
        static worm object;
        return object;
    }
    
    int getLenght()
    {
        return lenght;
    }

    void increase()
    {
        if (lenght<40)
            lenght++;
        else
            lenght = 3;
    }

    void decrease()
    {
        if (lenght>3)
            lenght--;
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

    void shift()
    {
        for (int i = lenght-1; i > 0; i--)                                      /* сдвигаем элементы червя на один вправо           */
        {                                                                       /*                                                  */
            ip_worm[i][0] = ip_worm[i-1][0];                                    /*                                                  */
            ip_worm[i][1] = ip_worm[i-1][1];                                    /*                                                  */
        }
    }

    void show( int color)                                                                         // вывод червя
    {
        int tailX, tailY, i;                                                          // хвостовой элемент, затирающий след
        for (i = 0; i<lenght; i++)
        {
            gotoXY(ip_worm[i][0], ip_worm[i][1], color);
            cout<<" ";
        }
        tailX = ip_worm[i][0];
        tailY = ip_worm[i][1];
        gotoXY(tailX, tailY, White);
        cout<<" ";
        return;
    }

private: 
    worm():lenght(3),direction(1)
    {    }
         
    ~worm()
    {    }

    worm(const worm&) = delete;
    worm& operator=(const worm&) = delete;
};

