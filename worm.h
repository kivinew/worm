#pragma once
#include "header.h"
using namespace std;
// класс Синглтон (приватный конструктор)
class worm
{
private:
    int size,                                                               // размер червя
        life,                                                               // количество жизней червя
        direction,                                                          // направление движения червя
        color,                                                              // цвет червя
        speed;                                                              // скорость червя
    char face;                                                              // лицо червя
    struct coordinates                                                      // структура массивов координат 40 элементов червя
    {int X[40], Y[40];
    }COORD;

public:
    static worm& getWorm()
    {
        static worm newWorm;
        return newWorm;
    }
    // размер червя
    int getLenght()
    {
        return size;
    }
    // изменить размер червя
    void sizeChange(int change)
    {
        if (change == RESET_VALUE)
            size = 3;
        else 
            size += change;
        return;
    }
    // установить направление
    void setDirection(int dir)
    {
        direction = dir;
        return;
    }
    // направление
    int getDirection()
    {
        return direction;
    }
    // значение задержки
    int getSpeed()
    {
        return speed;
    }
    // установить цвет червя
    void setColor(int newColor)
    {
        color = newColor;
    }
    // движение червя
    int move(prize *box)
    {
        int dX = 0, dY = 0,
            headX, headY;
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
        headX = COORD.X[0] + dX;                                            // сохраняем 
        headY = COORD.Y[0] + dY;                                            // новые координаты головы
        if (size < 3)
        {
            COORD.X[0] = 40;
            COORD.Y[0] = 12;
            life--;
            if (life < 1) return EXIT_SUCCESS;
            return RESTART_CODE;
        }
        // проверяем координаты головы на выход за пределы поля
        if (headX < 1 || headX > 78 || headY < 1 || headY > 23)
        {
            size--;                                                         // уменьшаем длину тела червяка.
            color = LightRed;
            return CONTINUE_CODE;
        }
        // проверка на столкновение головы с другими элементами его тела
        for (int i = 3; i < size; i++)                                      // 3 - чтобы не сталкиваться с головной частью тела
        {                                        
            if (headX == COORD.X[i])                                        // если координата Х совпала -
            {                                                               // проверяем
                if (headY == COORD.Y[i])                                    // координату У, если она
                {                                                           // тоже совпала, то ...
                    color = LightRed;                                       // затираем червяка белым цветом ...
                    size -= 3;                                              // уменьшаем длину тела и ...
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
                    color = box[i].color;
                    levelUp();
                }
            }
        }
        for (int i = size; i > 0; i--)                                      // сдвигаем элементы массива на один влево         
        {                                                                   //                                                  
            COORD.X[i] = COORD.X[i - 1];                                    //                                                  
            COORD.Y[i] = COORD.Y[i - 1];                                    //                                                  
        }
        COORD.X[0] = headX;                                                 // присваиваем значения координат
        COORD.Y[0] = headY;                                                 // головному элементу
        return CONTINUE_CODE;
    }
    // изменение скорости
    void speedUp(int speedChange)
    {
        if (speedChange == RESET_VALUE) speed = DEFAULT_SPEED;              // сброс скорости
        else speed -= speedChange;
        return;
    }
    // червь растёт и ускоряется
    void levelUp()
    {
        size++;                                                             //
        speed--;
        if (size > 40)
        {
            life++;
            speed -= 10;
            size = 3 + life;                                                // 
        }
        return;
    }
    // вывод червя
    void show()
    {
        int i;
        gotoXY(COORD.X[0], COORD.Y[0], LightRed);                           // голова
        cout << face;
        for (i = 1; i < size; i++)
        {
            gotoXY(COORD.X[i], COORD.Y[i], color);
            cout << " ";
        }
        gotoXY(COORD.X[i], COORD.Y[i], White);                              // затираем след за червём
        cout << " ";
        return;
    }

private:
    worm()
    {
        life = 3;
        size = 0;
        color = LightBlue;
        direction = right_dir;
        speed = 50;
        COORD.X[0] = 40;
        COORD.Y[0] = 12;
        face = ' ';
    }

    ~worm() {    }

    worm(const worm&) = delete;
    worm& operator=(const worm&) = delete;
};

