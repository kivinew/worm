#pragma once
class worm
{
    int lenght;
    int *ip_array = new int[lenght];            // ��������� �� ������������ ������
    int direction;                              // ����������� ��������
public:
    int* getArray()
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

    worm():lenght(3),direction(1)
    {
    }

    ~worm()
    {
    }

};

