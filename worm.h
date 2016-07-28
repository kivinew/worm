#pragma once
#include "header.h"
using namespace std;
// класс Синглтон (приватный конструктор)
class worm
{
private:
    int size,
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
        return size;
    }

    void sizeChange(int change)
    {
        size += change;
        
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

    int move(prize *box)
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
        if (size < 3)
        {
            COORD.X[0] = 40;
            COORD.Y[0] = 12;
            return RESTART_CODE;
        }
        // проверяем координаты головы на выход за пределы поля
        if (headX < 1 || headX > 78 || headY < 1 || headY > 23)
        {
            sizeChange(-1);                                                 // уменьшаем длину тела червяка.
            color = LightRed;
            return CONTINUE_CODE;
        }
        // проверка на столкновение головы с другими элементами его тела
        for (int i = 4; i < getLenght() - 1; i++)
        {                                                                   //  -1 чтобы не сталкиваться с невидимой частью хвоста
            if (headX == COORD.X[i])                                        // если координата Х совпала -
            {                                                               // проверяем
                if (headY == COORD.Y[i])                                    // координату У, если она
                {                                                           // тоже совпала, то ...
                    color = LightRed;                                       // затираем червяка белым цветом ...
                    sizeChange(-3);                                         // уменьшаем длину тела и ...
                }
            }
        }
        // проверка координат головы на совпадение с координатами призов
        for (int i = 0; i < prize::getCount(); i++)
        {
            if (headX == box[i].x)
            {
                if (headY == box[i].y)                                      //
                {                                                           //
                    sizeChange(1);                                          //
                    color = LightBlue;
                    if (size > 40)
                    {
                        life++;
                        size = 3;
                    }
                }
            }
        }

        for (int i = size - 1; i > 0; i--)                                  /* сдвигаем элементы массива на один вправо         */
        {                                                                   /*                                                  */
            COORD.X[i] = COORD.X[i - 1];                                    /*                                                  */
            COORD.Y[i] = COORD.Y[i - 1];                                    /*                                                  */
        }
        COORD.X[0] = headX;
        COORD.Y[0] = headY;
        return CONTINUE_CODE;
    }

    void show()                                                             // вывод червя
    {
        for (int i = 0; i < size; i++)
        {
            gotoXY(COORD.X[i], COORD.Y[i], color);
            cout << " ";
        }
        Sleep(40);                                                          // задержка
        for (int i = 0; i < size; i++)
        {
            gotoXY(COORD.X[i], COORD.Y[i], White);
            cout << " ";
        }
        return;
    }

private:
    worm()
    {
        size = 3;
        color = LightBlue;
        direction = right_dir;
        COORD.X[0] = 40;
        COORD.Y[0] = 12;
    }

    ~worm() {    }

    worm(const worm&) = delete;
    worm& operator=(const worm&) = delete;
};

