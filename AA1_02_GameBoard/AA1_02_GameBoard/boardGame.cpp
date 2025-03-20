#include <iostream>
#include <math.h>
#include <time.h>
#include <string>
#include <fstream>
#include "boardGame.h"

int main()
{

    std::ifstream settings("settings.txt");

    if (settings.is_open())
    {

        while(settings >> x >> y){}

    }
    settings.close();

    srand(time(NULL));

    Player pepito;
    Cell** board;
    PlayerMovement mov;
    bool cont = false;

    board = new Cell * [x];
    for (int i = 0; i < x; ++i)
    {
        board[i] = new Cell[y];
    }

    initializeBoard(board, pepito);

    do
    {
        system("CLS");
        printBoard(board);
        std::cout << pepito.x << " " << pepito.y << std::endl;
        std::cout << "UP = W, LEFT = A, DOWN = S, RIGHT = D" << std::endl;


        do
        {
            std::cout << "Input movement: ";
            char input;
            std::cin >> input;

            switch (input)
            {
            case 'w':
            case 'W':
                mov = PlayerMovement::UP;
                cont = false;
                break;
            case 'a':
            case 'A':
                mov = PlayerMovement::LEFT;
                cont = false;
                break;
            case 's':
            case 'S':
                mov = PlayerMovement::DOWN;
                cont = false;
                break;
            case 'd':
            case 'D':
                mov = PlayerMovement::RIGHT;
                cont = false;
                break;
            default:
                std::cout << "Invalid input. Try again." << std::endl;
                break;
            }
        } while (cont);

        if (checkMovement(pepito, mov))
        {

            cont = gameOver(pepito, board, mov);

            if (existGem(pepito, mov, board))
            {
                addScore(pepito);
            }

            movePlayer(pepito, board, mov);
            setPosition(pepito, mov);
        }

    } while (!cont);

    destroyBoard(board);

    return 0;
}