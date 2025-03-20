#pragma once
#include <iostream>
#include <math.h>
#include <time.h>
#include <string>

int x;
int y;

enum class PlayerMovement
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class Cell
{
    PARED,
    PINCHO,
    GEMA,
    JUGADOR,
    VACIO
};

struct Player
{
    int x;
    int y;
    int score;
};

void initializeBoard(Cell** board, Player& player)
{
    // Initialize all cells to VACIO
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            board[j][i] = Cell::VACIO;
        }
    }

    // Set the borders to PARED
    for (int i = 0; i < x; i++)
    {
        board[i][0] = Cell::PARED;
        board[i][y - 1] = Cell::PARED;
    }

    for (int i = 0; i < y; i++)
    {
        board[0][i] = Cell::PARED;
        board[x - 1][i] = Cell::PARED;
    }

    // Place random PINCHOs
    int numPinchos = rand() % (((x - 1) * (y - 1)) / 10);
    for (int i = 0; i <= numPinchos; i++)
    {
        int px, py;
        do
        {
            px = rand() % (x - 1);
            py = rand() % (y - 1);
        } while (board[px][py] != Cell::VACIO);
        board[px][py] = Cell::PINCHO;
    }

    // Place random GEMAs
    int numGemas = rand() % (((x - 1) * (y - 1)) / 4);
    for (int i = 0; i <= numGemas; i++)
    {
        int gx, gy;
        do
        {
            gx = rand() % (x - 1);
            gy = rand() % (y - 1);
        } while (board[gx][gy] != Cell::VACIO);
        board[gx][gy] = Cell::GEMA;
    }

    // Place the player
    int plx, ply;
    do
    {
        plx = rand() % (x - 1);
        ply = rand() % (y - 1);
    } while (board[plx][ply] != Cell::VACIO);
    board[plx][ply] = Cell::JUGADOR;
    player.x = plx;
    player.y = ply;
}

void printBoard(Cell** board)
{
    char sym;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            switch (board[j][i])
            {
            case Cell::PARED:
                sym = 254;
                std::cout << sym << " ";
                break;
            case Cell::PINCHO:
                sym = 193;
                std::cout << sym << " ";
                break;
            case Cell::GEMA:
                sym = 248;
                std::cout << sym << " ";
                break;
            case Cell::JUGADOR:
                sym = 80;
                std::cout << sym << " ";
                break;
            default:
                sym = 255;
                std::cout << sym << " ";
                break;
            }
        }
        std::cout << std::endl;
    }
}

bool checkMovement(Player player, PlayerMovement mov)
{
    switch (mov)
    {
    case PlayerMovement::UP:
        return player.y > 1;
    case PlayerMovement::DOWN:
        return player.y < y - 2;
    case PlayerMovement::LEFT:
        return player.x > 1;
    case PlayerMovement::RIGHT:
        return player.x < x - 2;
    }
}

void addScore(Player& player)
{
    player.score += 1;
}

void setPosition(Player& player, PlayerMovement mov)
{
    switch (mov)
    {
    case PlayerMovement::UP:
        player.y -= 1;
        break;
    case PlayerMovement::DOWN:
        player.y += 1;
        break;
    case PlayerMovement::LEFT:
        player.x -= 1;
        break;
    case PlayerMovement::RIGHT:
        player.x += 1;
        break;
    }
}

bool existGem(Player& player, PlayerMovement mov, Cell** board)
{
    switch (mov)
    {
    case PlayerMovement::UP:
        return board[player.x][player.y - 1] == Cell::GEMA;
    case PlayerMovement::DOWN:
        return board[player.x][player.y + 1] == Cell::GEMA;
    case PlayerMovement::LEFT:
        return board[player.x - 1][player.y] == Cell::GEMA;
    case PlayerMovement::RIGHT:
        return board[player.x + 1][player.y] == Cell::GEMA;
    }
    return false;
}

void movePlayer(Player& player, Cell** board, PlayerMovement mov)
{
    board[player.x][player.y] = Cell::VACIO;
    switch (mov)
    {
    case PlayerMovement::UP:
        board[player.x][player.y - 1] = Cell::JUGADOR;
        break;
    case PlayerMovement::DOWN:
        board[player.x][player.y + 1] = Cell::JUGADOR;
        break;
    case PlayerMovement::LEFT:
        board[player.x - 1][player.y] = Cell::JUGADOR;
        break;
    case PlayerMovement::RIGHT:
        board[player.x + 1][player.y] = Cell::JUGADOR;
        break;
    }
}

bool gameOver(Player player, Cell** board, PlayerMovement mov)
{
    // Check if player steps on a PINCHO
    switch (mov)
    {
    case PlayerMovement::UP:
        if (board[player.x][player.y - 1] == Cell::PINCHO)
        {
            system("CLS");
            std::cout << "You lost...";
            return true;
        }
        break;
    case PlayerMovement::DOWN:
        if (board[player.x][player.y + 1] == Cell::PINCHO)
        {
            system("CLS");
            std::cout << "You lost...";
            return true;
        }
        break;
    case PlayerMovement::LEFT:
        if (board[player.x - 1][player.y] == Cell::PINCHO)
        {
            system("CLS");
            std::cout << "You lost...";
            return true;
        }
        break;
    case PlayerMovement::RIGHT:
        if (board[player.x + 1][player.y] == Cell::PINCHO)
        {
            system("CLS");
            std::cout << "You lost...";
            return true;
        }
        break;
    }

    // Check if all gems are collected
    int gemCount = 0;
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (board[j][i] == Cell::GEMA)
            {
                gemCount++;
            }
        }
    }

    if (existGem(player, mov, board) && gemCount < 2)
    {
        system("CLS");
        std::cout << "You WIN :)";
        return true;
    }

    return false;
}

void destroyBoard(Cell** board)
{
    for (int i = 0; i < x; ++i)
    {
        delete[] board[i];
    }
    delete[] board;
}
