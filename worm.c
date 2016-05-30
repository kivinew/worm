///    "Червяк". По экрану движется червяк, направление движения головы которого
///    можно менять (стрелками). Червяк ест призы и растет. Задача - при движении
///    головы не наткнуться на хвост и границы экрана.
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
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

void newGame    ( );                                                            // новая игра
void newPrize   ( );                                                            // вывод приза
int  crawling   ( int [] [2] , int* , int , int );                              // управление процессом игры
int  wormBuilt  ( int [] [2] , int* , int , int );
void worm       ( int [] [2] , int* , int       );
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

//struct PRIZE
//{
//    int             x;
//    int             y;
//    char            face;
//    unsigned int    color;
//    int             wormColor;
//} prize[10];

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
        prize[0] . color = LightGreen ;                                            // начальный цвет червя
        newPrize ( ) ;
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

void newPrize   ( )                                                             // сгенерировать случайные координаты
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i<10; i++)
    {
        rand();                                                                  // для сбивания первого неслучайного значения
        int x, y, face, color;
        x = rand()%78+1;                                                     // координаты Х....
        y = rand()%23+1;                                                     // и Y.
        face = ' ';                                                                // это символ которым обозначен на поле приз
        color = rand()%7+8;
        prize[i].wormColor = prize[i].color;
        prize[i].color = color;
        prize[i].x = x;                                                             // присвоить свойства приза ...
        prize[i].y = y;                                                             // ... полям структуры prize
        prize[i].face = face;
        gotoXY(x, y, color);                                                  // ... а тут эти свойства ...
        printf("%c", face);                                                    // ... используются для вывода приза
    }
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

    for (int j = 0; j<10; j++) 
    {
        if (tmpX==prize[j].x)                                                    // проверка координат головы
        {                                                                           // на совпадение с координатами фруктов
            if (tmpY==prize[j].y)                                                //
            {                                                                       //
                ++ *lenght;                                                        //
                worm(wormArray, lenght, prize[j].color+8);                    //
                Sleep(20);                                                     //
                if (*lenght>MAX_SIZE)                                           // увеличиваем длину червя и проверяем
                {                                                                   // её на превышение максимума.
                    return RESTART_CODE;                                            // если длина максимальна, перезапускаем игру ...
                }                                                                   //
                for (int i = 0; i<10; i++)
                {
                    int x = prize[i].x;
                    int y = prize[i].y;
                    gotoXY(x, y, White);
                    printf(" ");
                }
                newPrize();                                                       // создаем новый приз
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
    worm ( wormArray , lenght , prize[0] . wormColor ) ;                           /* вывод тела червя цветом найденного приза         */
    return CONTINUE_CODE;
}

void worm       ( int wormArray [] [2] , int *lenght , int wormColor )          // вывод червя
{
    int i ;
    for ( i = 0 ; i < *lenght - 1 ; i++ )
    {
        int x , y ;
        x = wormArray [i] [0] ;
        y = wormArray [i] [1] ;
        gotoXY ( x , y , wormColor - 8 ) ;
        printf ( "%c", 32 ) ;
    }
    int tailX , tailY;                                                          // хвостовой элемент, затирающий след
    tailX = wormArray [i] [0] ;
    tailY = wormArray [i] [1] ;
    gotoXY ( tailX , tailY , White ) ;
    printf ( "%c" , 32 );
    return ;
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
