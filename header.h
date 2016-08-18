#pragma once
#include <time.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#ifndef MYLIBS_H_INCLUDED
// обозначения кодов и клавиш
#define MYLIBS_H_INCLUDED
#define ESC                 27
#define ENTER               13
#define RESET_VALUE         0                                                   // сброс значения 
#define DEFAULT_SPEED       60                                                  // задержка по умолчанию
#define LEFT_KEY            75
#define RIGHT_KEY           77
#define UP_KEY              72
#define DOWN_KEY            80
#define left_dir             1
#define right_dir            2
#define up_dir               3
#define down_dir             4
#define MAX_SIZE            45
#define RESTART_CODE        -1                                                  // код перезапуска игры
#define CONTINUE_CODE       1                                                   // код продолжения
#define EXIT_SUCCESS        0                                                   // код нормального выхода
#define EXIT_DEBUG_EVENT    5                                                   // отладочный код выхода
// перечисление цветов вывода в консоль
enum Color {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};
// перевод курсора в положение X,Y и назначение цвета фона
void gotoXY(int x, int y, int back)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(console, coord);                              // позиция курсора
    SetConsoleTextAttribute(console, (WORD) (back << 4));                // цвет фона
    return;
}
#endif
