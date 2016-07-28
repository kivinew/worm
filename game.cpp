//    "Червяк". По экрану движется червяк, направление движения головы которого
//    можно менять (стрелками). Червяк ест призы и растет. Задача - при движении
//    головы не наткнуться на хвост и границы экрана.

#include "header.h"
#include "prize.h"
#include "worm.h"

using namespace std;

void newGame();                                                                 // новая игра
int  crawling();                                                                // управление процессом игры

prize box[10];
worm &WORM = worm::getWorm();
int main()
{
    SetCursorPos(600, 0);
    SetConsoleTitleA("WORM.objected: ESC - exit, ENTER - restart, arrow keys - driving worm");
    newGame();
    return EXIT_DEBUG_EVENT;
}
// новая игра
void newGame()
{
    gotoXY(0, 0, White);                                                        // установим цвет фона белым
    int quiteCode = 0;                                                          // переменная-признак
    system("cls");
    do
    {
        WORM.sizeChange(0);                                                     // 0 - сброс размера червя
        for each(prize nextBox in box)
        {
            nextBox.showPrize();
        }
        quiteCode = crawling();                                                 // crawling() возвращает код выхода RESTART_CODE или EXIT_SUCCESS
                                                                                // в переменную-признак.
        if (quiteCode == EXIT_SUCCESS) return;                                  // выход из игры
    } while (quiteCode == RESTART_CODE);                                        // циклический вызов новой игры
    return;
}
// управление процессом игры
int crawling()
{
    do                                                                          // бесконечный цикл ________________
    {                                                                           //                                  |
        while (!_kbhit())                                                       //                                  |
        {                                                                       //                                  |
            WORM.show();                                                        // вывод червя
            int resultCode = WORM.move(box);                                    //                       ОСНОВНОЙ   |
            if (resultCode != CONTINUE_CODE) return resultCode;                 //                     РАБОЧИЙ ЦИКЛ |
        }                                                                       //                                  |
        char pressedKey = _getch();                                             //                                  |
        switch (pressedKey)                                                     //                                  |
        {                                                                       //                                  |
        case ESC:                                                               //                                  |
            system("cls");                                                      //                                  |
            return EXIT_SUCCESS;                                                //                                  |
            break;                                                              //                                  |
        case ENTER:                                                             //                                  |
            return RESTART_CODE;                                                //                                  |
            break;                                                              //                                  |
        case LEFT_KEY:                                                          //                                  |
            if (WORM.getDirection() != right_dir)                               // Если не двигаемся вправо,        |
            {                                                                   //                                  |
                WORM.setDirection(left_dir);                                    // то двигаемся влево.              |
            }                                                                   //                                  |
            break;                                                              //                                  |
        case RIGHT_KEY:                                                         //                                  |
            if (WORM.getDirection() != left_dir)                                // Если не двигаемся влево,         |
            {                                                                   //                                  |
                WORM.setDirection(right_dir);                                   // то двигаемся вправо.             |
            }                                                                   //                                  |
            break;                                                              //                                  |
        case UP_KEY:                                                            //                                  |
            if (WORM.getDirection() != down_dir)                                // Если не двигаемся вниз,          |
            {                                                                   //                                  |
                WORM.setDirection(up_dir);                                      // то двигаемся вверх.              |
            }                                                                   //                                  |
            break;                                                              //                                  |
        case DOWN_KEY:                                                          //                                  |
            if (WORM.getDirection() != up_dir)                                  // Если не двигаемся вверх,         |
            {                                                                   //                                  |
                WORM.setDirection(down_dir);                                    // то двигаемся вниз.               |
            }                                                                   //                                  |
            break;                                                              //                                  |
        case '+':                                                               //                                  |
            WORM.speedUp(1);                                                    //                                  |
            break;                                                              //                                  |
        case '-':                                                               //                                  |
            WORM.speedUp(-1);                                                   //                                  |
            break;                                                              //                                  |
        }                                                                       //                                  |
    } while (TRUE);                                                             // бесконечный цикл ________________|
    return EXIT_DEBUG_EVENT;
}