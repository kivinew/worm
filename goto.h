#ifndef MYLIBS_H_INCLUDED
#define MYLIBS_H_INCLUDED
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
#endif
