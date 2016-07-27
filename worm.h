#pragma once
#include "header.h"
using namespace std;

class worm
{
private:
    int length,
        life,
        direction,
        color;                                                              // направление движения;
    struct coordinates
    {
        int X[40], Y[40];
    }COORD;                                                                 // структура массивов координат 40 элементов червя

public:
    static worm& getWorm()
    {
        static worm newWorm;
        return newWorm;
    }

    int getLenght()
    {
        return length;
    }

    void lengthChange(int change)
    {
        length += change;
        if (length > 40)
        {
            life++;
            length = 3;
        }
        else if (length < 3)
        {
            exit(0);
        }
        return;
    }

    void setDirection(int dir)
    {
        direction = dir;
        return;
    }

    int getDirection()
    {
        return direction;
    }

    void setColor(int newColor)
    {
        color = newColor;
    }

    int getX()
    {
        return COORD.X[0];
    }

    int getY()
    {
        return COORD.Y[0];
    }

    void move(prize *box)
    {
        int dX = 0, dY = 0,
            headX = COORD.X[0],
            headY = COORD.Y[0];
        switch (direction)
        {
        case left_dir:
            dX = -1;
            break;
        case right_dir:
            dX = 1;
            break;
        case up_dir:
            dY = -1;
            break;
        case down_dir:
            dY = 1;
            break;
        }
        headX += dX;
        headY += dY;
        // проверяем координаты головы на выход за пределы поля
        if (headX < 1 || headX > 78 || headY < 1 || headY > 23)
        {
            lengthChange(-1);                                               // уменьшаем длину тела червяка.
            return;
        }
        // проверка на столкновение головы с другими элементами его тела
        //for (int i = 4; i < getLenght() - 1; i++)
        //{                                                                   //  -1 чтобы не сталкиваться с невидимой частью хвоста
        //    if (headX == COORD.X[i])                                        // если координата Х совпала -
        //    {                                                               // проверяем
        //        if (headY == COORD.Y[i])                                    // координату У, если она
        //        {                                                           // тоже совпала, то ...
        //            //show(LightRed);
        //            //show(White);                                          // затираем червяка белым цветом ...
        //            lengthChange(-3);                                       // уменьшаем длину тела и ...
        //            //show(LightRed);                                         // ... выводим червя нового размера
        //        }
        //    }
        //}
        // проверка координат головы на совпадение с координатами призов
        for (int i = 0; i < prize::getCount(); i++)
        {
            if (headX == box[i].x)
            {
                if (headY == box[i].y)                                      //
                {                                                           //
                    lengthChange(1);                                        //
                }
            }
        }

        for (int i = length - 1; i > 0; i--)                                /* сдвигаем элементы массива на один вправо         */
        {                                                                   /*                                                  */
            COORD.X[i] = COORD.X[i - 1];                                    /*                                                  */
            COORD.Y[i] = COORD.Y[i - 1];                                    /*                                                  */
        }
        COORD.X[0] = headX;
        COORD.Y[0] = headY;
        return;
    }

    void show()                                                             // вывод червя
    {
        for (int i = 0; i < length; i++)
        {
            gotoXY(COORD.X[i], COORD.Y[i], color);
            cout << " ";
        }
        Sleep(40);                                                          // задержка
        for (int i = 0; i < length; i++)
        {
            gotoXY(COORD.X[i], COORD.Y[i], White);
            cout << " ";
        }
        return;
    }

private:
    worm(): length(5), color(7)
    {
        direction = right_dir;
        COORD.X[0] = 40;
        COORD.Y[0] = 12;
    }

    ~worm()
    {    }

    worm(const worm&) = delete;
    worm& operator=(const worm&) = delete;
};

