#pragma once
#include <iostream>
using namespace std;

class worm
{
    int lenght;
    int **ip_array = new int*[2];                       // указатель на динамический массив
    int direction;                                      // направление движения
public:
    int** getArray()
    {
        return ip_array;
    }
    
    int getLenght()
    {
        return lenght;
    }

    void increase()
    {
        lenght++;
    }

    void decrease()
    {
        lenght--;
    }

    void setDirection(int dir)
    {
        direction = dir;
    }

    void showWorm()
    {
        for (int i = 0; i<lenght-1; i++)
        {
            int x, y;
            x = ip_array[i][0];
            y = ip_array[i][0];

        }
    }

    worm():lenght(3),direction(1)
    {
    }

    ~worm()
    {
    }

};

