#pragma once

class prize
{
    int             x;
    int             y;
    char            face;
    int             color;
    bool            state;
    int static      count;
public:

    prize(): x(0), y(0), color(14)
    {
    }

    ~prize()
    {
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    char getFace()
    {
        return face;
    }

    int getColor()
    {
        return color;
    }
    
    void setState()
    {
        if (count>10)
            state = 0;
        else
            state = 1;
    }

    int getState()
    {
        return state;
    }

    //void newPrize()                                                             // сгенерировать случайные координаты
    //{
    //    prize box;
    //    srand((unsigned int)time(NULL));
    //    rand();                                                                 // для сбивания первого неслучайного значения
    //    x = rand()%78+1;                                                        // координаты Х....
    //    y = rand()%23+1;                                                        // и Y.
    //    face = ' ';                                                             // это символ которым обозначен на поле приз
    //    wormColor = getColor();
    //    color = rand()%7+8;
    //    return;
    //}
};