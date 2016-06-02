#pragma once
#include <iostream>
using namespace std;

class worm
{
    int lenght;
    static int **ip_worm;                              // указатель на динамический массив
    int direction;                                              // направление движения

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

    void show()
    {
        for (int i = 0; i<lenght-1; i++)
        {
            int x, y;
            x = ip_worm[i][0];
            y = ip_worm[i][1];
                                                    /// ----------------------?-------------------------------
        }
    }

private: 
    worm():lenght(3),direction(1)
    {    }
         
    ~worm()
         {    }

    worm(const worm&) = delete;
    worm& operator=(const worm&) = delete;
};

