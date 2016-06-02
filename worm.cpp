///    "Червяк". По экрану движется червяк, направление движения головы которого
///    можно менять (стрелками). Червяк ест призы и растет. Задача - при движении
///    головы не наткнуться на хвост и границы экрана.
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "prize.h"
#include "worm.h"

#define ESC                 27
#define ENTER               13
#define LEFT                75
#define UP                  72
#define RIGHT               77
#define DOWN                80
#define MAX_SIZE            45
#define RESTART_CODE        -1                                                  // код перезапуска игры
#define CONTINUE_CODE       1                                                   // код продолжения
#define EXIT_SUCCESS        0                                                   // код нормального выхода
#define EXIT_DEBUG_EVENT    5                                                   // отладочный код выхода

using namespace std;

void newGame    ( );                                                            // новая игра
int  crawling   ( int [] [2] , int* , int , int );                              // управление процессом игры
int  wormBuilt  ( int [] [2] , int* , int , int );
void Worm       ( int [] [2] , int* , int       );
void newBox     ( prize                         );
void gotoXY     ( int        , int  , int       );

enum Color {                                                                    // перечисление цветов вывода в консоль
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

prize box[10];

int main        ( )
{
    SetCursorPos ( 600 , 0 ) ;
    SetConsoleTitleA( "WORM: ESC - exit, ENTER - restart, arrow keys for driving worm" ) ;
    newGame ( ) ;
    return 0 ;
}

void newGame    ( )                                                             // новая игра
{
    gotoXY ( 0 , 0 , White );                                                   // установим цвет фона белым
    int quiteCode ;                                                             // переменная-признак
    do
    {
        system ( "cls" ) ;
        int lenght = MAX_SIZE - 41 ;                                            // длина червя
        int wormArray [ MAX_SIZE ] [ 2 ] = { 40 , 12 } ;                        // начальные координаты червя
        for (int i = 0; i<10; i++)
        {
            newBox(box[i]);
        }
        int dX, dY ;
        dY = 0 ;
        dX = rand ( ) % 3 - 1 ;
        if ( dX == 0 ) dY = 1 ;
        quiteCode = crawling ( wormArray , &lenght , dX , dY ) ;                // crawling() возвращает код выхода RESTART_CODE или EXIT_SUCCESS
                                                                                // в переменную-признак. В аргументах массив с элементами
                                                                                // тела червя, длина червя и сдвиги по осям Х и У.
        if ( quiteCode == EXIT_SUCCESS ) return ;                               // выход из игры
    } while ( quiteCode == RESTART_CODE ) ;                                     // циклический вызов новой игры
    return ;
}

int crawling    ( int wormArray [] [2] , int *lenght , int dX , int dY )        // управление процессом игры
{
    do                                                                          // бесконечный цикл
    {
        int resultCode;
        while (!_kbhit())
        {
            resultCode = wormBuilt ( wormArray , lenght , dX , dY ) ;           //  ОСНОВНОЙ                        |
            if ( resultCode != CONTINUE_CODE ) return resultCode ;              //  РАБОЧИЙ                         |
            Sleep ( 60 ) ;                                                      //  ЦИКЛ                            |
        }
        char pressedKey = _getch ( );
        switch ( pressedKey )
        {
        case ESC:
            system ("cls");
            return EXIT_SUCCESS;
            break;
        case ENTER:
            return RESTART_CODE ;
            break;
        case LEFT:
            if ( dX != 1 )                                                      // Если не двигаемся вправо,
            {
                dX = -1 ;                                                       // смещение по оси Х влево.
                dY = 0 ;
            }
            break;
        case RIGHT:
            if ( dX != -1 )                                                     // Если не двигаемся влево,
            {
                dX = 1 ;                                                        // смещение по оси Х вправо.
                dY = 0 ;
            }
            break;
        case UP:
            if ( dY != 1 )                                                      // Если не двигаемся вниз,
            {
                dY = -1 ;                                                       // то двигаемся вверх.
                dX = 0 ;
            }
            break;
        case DOWN:
            if ( dY != -1 )                                                     // Если не двигаемся вверх,
            {
                dY = 1 ;                                                        // то двигаемся вниз.
                dX = 0 ;
            }
            break;
        }
    } while ( TRUE ) ;                                                          // бесконечный цикл
    return EXIT_PROCESS_DEBUG_EVENT;
}

int wormBuilt   ( int wormArray [] [2] , int *lenght , int dX , int dY )        // изменение массива с координатами тела червя ...
{                                                                               // ... и проверки на столкновения
    int tmpX , tmpY ;
    tmpX = wormArray [ 0 ] [ 0 ] + dX ;                                         // сохраняем координаты головы червя
    tmpY = wormArray [ 0 ] [ 1 ] + dY ;                                         // и прибавляем смещение
    int i ;
    for ( i = 4 ; i < *lenght - 1 ; i++ )                                       // проверка на столкновение головы с другими элементами его
    {                                                                           // тела, -1 чтобы не сталкиваться с невидимой частью хвоста
        if (tmpX == wormArray[i][0])                                            // если координата Х совпала -
        {                                                                       // проверяем
            if (tmpY == wormArray[i][1])                                        // координату У, если она
            {                                                                   // тоже совпала, то ...
                worm ( wormArray , lenght , LightRed + 8 ) ;
                worm ( wormArray , lenght , White + 8 ) ;                       // затираем червяка белым цветом ...
                *lenght -= 3;                                                   // уменьшаем длину тела и ...
                worm ( wormArray , lenght , LightRed + 8 ) ;                    // ... выводим червя нового размера
                return CONTINUE_CODE;                                           // ... играем дальше
            }
        }
    }
    if ( tmpX < 1 || tmpX > 78 || tmpY < 1 || tmpY > 23 )                       // проверка на выход за границы поля
    {                                                                           //
        --*lenght ;                                                             // уменьшаем длину тела червяка
        worm ( wormArray , lenght , LightRed + 8 ) ;                            //
        if ( *lenght < 3 )                                                      // если длина стала минимальной ...
        {                                                                       // ...
            if ( _getch ( ) == ESC ) return EXIT_SUCCESS;                       // ...
            return RESTART_CODE;                                                // играем заново,
        }                                                                       // а если нет...
        return CONTINUE_CODE ;                                                  // ... то движемся дальше
    }

    for (int i = 0; i<10; i++) 
    {
        if (tmpX==box[i].getX())                                                // проверка координат головы
        {                                                                       // на совпадение с координатами фруктов
            if (tmpY==box[i].getY())                                            //
            {                                                                   //
                ++ *lenght;                                                     //
                worm(wormArray, lenght, box[i].getColor()+8);                   //
                Sleep(20);                                                      //
                if (*lenght>MAX_SIZE)                                           // увеличиваем длину червя и проверяем
                {                                                               // её на превышение максимума.
                    return RESTART_CODE;                                        // если длина максимальна, перезапускаем игру ...
                }                                                               //
                /*for (int i = 0; i<10; i++)
                {
                    int x = box[i].getX();
                    int y = box[i].getY();
                    gotoXY(x, y, White);
                    printf(" ");
                }*/
            }
        }
    }
    for ( i = *lenght - 1 ; i > 0 ; i-- )                                       /* сдвигаем элементы червя на один вправо           */
    {                                                                           /*                                                  */
        wormArray [i] [0] = wormArray [i - 1] [0] ;                             /*                                                  */
        wormArray [i] [1] = wormArray [i - 1] [1] ;                             /*                                                  */
    }                                                                           /*                                                  */
    wormArray [0] [0] = tmpX ;                                                  /* восстанавливаем координаты головы                */
    wormArray [0] [1] = tmpY ;                                                  /*                                                  */
    worm ( wormArray , lenght , box[0] . getWormColor() ) ;                     /* вывод тела червя цветом найденного приза         */
    return CONTINUE_CODE;
}

void Worm       ( int wormArray [] [2] , int *lenght , int wormColor )          // вывод червя
{
    worm& ptr = worm::getWorm();
    int tailX , tailY;                                                          // хвостовой элемент, затирающий след
    int i;
    tailX = wormArray [i] [0] ;
    tailY = wormArray [i] [1] ;
    gotoXY ( tailX , tailY , White ) ;
    printf ( "%c" , 32 );
    return ;
}

void newBox(prize box)
{
    gotoXY(box.getX(), box.getY(),box.getColor());
    cout<<box.getFace();
}

void gotoXY     ( int x , int y , int back )                                    // перевод курсора в положение X,Y
{                                                                               // и задание цвета символа
    HANDLE console = GetStdHandle ( STD_OUTPUT_HANDLE ) ;
    COORD coord ;
    coord . X = x ;
    coord . Y = y ;
    SetConsoleCursorPosition ( console , coord ) ;                              // позиция курсора
    SetConsoleTextAttribute ( console , (WORD) ( back << 4 ) ) ;                // цвет фона
    return;
}
