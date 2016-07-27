﻿///    "Червяк". По экрану движется червяк, направление движения головы которого
///    можно менять (стрелками). Червяк ест призы и растет. Задача - при движении
///    головы не наткнуться на хвост и границы экрана.

#include "prize.h"
#include "worm.h"
#include "header.h"

using namespace std;

void newGame();                                                             // новая игра
int  crawling();                                                            // управление процессом игры
int  wormShow();
void newBox(prize);
void gotoXY(int, int, int);


prize box[10];
worm &WORM = worm::getWorm();

int main()
{
    SetCursorPos(600, 0);
    SetConsoleTitleA("WORM.objected: ESC - exit, ENTER - restart, arrow keys - driving worm");
    newGame();
    return EXIT_DEBUG_EVENT;
}

void newGame()                                                                  // новая игра
{
    gotoXY(0, 0, White);                                                        // установим цвет фона белым
    int quiteCode;                                                              // переменная-признак
    do
    {
        system("cls");
        for (int i = 0; i < box[0].getCount(); i++)
        {
            newBox(box[i]);
        }
        quiteCode = crawling();                                                 // crawling() возвращает код выхода RESTART_CODE или EXIT_SUCCESS
                                                                                // в переменную-признак. В аргументах массив с элементами
                                                                                // тела червя, длина червя и сдвиги по осям Х и У.
        if (quiteCode == EXIT_SUCCESS) return;                                  // выход из игры
    } while (quiteCode == RESTART_CODE);                                        // циклический вызов новой игры
    return;
}
// управление процессом игры
int crawling()
{
    do                                                                          // бесконечный цикл
    {
        while (!_kbhit())
        {
            int resultCode = wormShow();                                       //  ОСНОВНОЙ                        |
            if (resultCode != CONTINUE_CODE) return resultCode;                 //  РАБОЧИЙ                         |
        }
        char pressedKey = _getch();
        switch (pressedKey)
        {
        case ESC:
            system("cls");
            return EXIT_SUCCESS;
            break;
        case ENTER:
            return RESTART_CODE;
            break;
        case LEFT_KEY:
            if (WORM.getDirection() != left_dir)                                // Если не двигаемся вправо,
            {
                WORM.setDirection(left_dir);                                    // смещение по оси Х влево.
            }
            break;
        case RIGHT_KEY:
            if (WORM.getDirection() != right_dir)                                // Если не двигаемся влево,
            {
                WORM.setDirection(right_dir);                                   // смещение по оси Х влево.
            }
            break;
        case UP_KEY:
            if (WORM.getDirection() != up_dir)                                    // Если не двигаемся влево,
            {
                WORM.setDirection(up_dir);                                      // смещение по оси Х влево.
            }
            break;
        case DOWN_KEY:
            if (WORM.getDirection() != down_dir)                                                     // Если не двигаемся влево,
            {
                WORM.setDirection(down_dir);                                         // смещение по оси Х влево.
            }
            break;
        }
    } while (TRUE);                                                             // бесконечный цикл
    return EXIT_DEBUG_EVENT;
}
// вывод тела червя ...
int wormShow()                                           
{
    WORM.move();
    WORM.show(Blue);                                                        /* вывод тела червя цветом найденного приза         */
    Sleep(40);
    WORM.show(White);                                                       /* вывод тела червя цветом найденного приза         */
    return CONTINUE_CODE;
}
// вывод нового приза
void newBox(prize box)
{
    gotoXY(box.getX(), box.getY(), box.getColor());
    cout << box.getFace();
}

