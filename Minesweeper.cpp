/*
Minesweeper game using CPP
Made by: just_another_3d_object
*/
#include <iostream>
#include <ctime>
#include <utility>
#include <algorithm>
#include <cstdlib>

#define MAXSIDE 25
#define MAXMINES 99
#define BEGINNER 1
#define INTERMEDIATE 2
#define ADVANCED 3
#define MINE '*'
#define FREE_CELL '-'

using namespace std;

int lines, columns, mines, level;
int x, y;
char real_board[MAXSIDE][MAXSIDE], player_board[MAXSIDE][MAXSIDE];

int difficulty_level()
{

    cout << "Enter difficulty level" << endl;
    cout << "Press 1 for BEGINNER" << endl;
    cout << "Press 2 for INTERMEDIATE" << endl;
    cout << "Press 3 for ADVANCED" << endl;

    cin >> level;
    if (level == BEGINNER) // declaring no of mines, lines and columns for every level
    {
        mines = 10;
        lines = 9;
        columns = 9;
    }

    if (level == INTERMEDIATE)
    {
        mines = 40;
        lines = 16;
        columns = 16;
    }

    if (level == ADVANCED)
    {
        mines = 73;
        lines = 21;
        columns = 21;
    }
    return level;
}

void place_mines() // function to place mines randomly
{
    int countmines;            // varible to count no of mines
    srand(time(NULL));         // Is used to reset the seed for rand function every time it's called
    while (countmines < mines) // until all mines are placed
    {
        int random = rand() % (lines * columns); // generating random number
        int i = random / columns;
        int j = random % lines;

        if (real_board[i][j] == MINE) // IF already a mine, continue
        {
            continue;
        }
        real_board[i][j] = MINE; // Place mine at i , j
        countmines++;
    }
}

bool is_mine(int x, int y) // checking function for mine

{
    if (real_board[x][y] == MINE)
    {
        return (true);
    }
    else
    {
        return (false);
    }
}

int compute_neighbours(int k, int l) // computes the nearby mines
{
    int minecount{0};
    for (int i = -1; i <= 1; i++) // covering the 8 spaces around a cell that has opened
    {
        for (int j = -1; j <= 1; j++) // covering the 8 spaces around a cell that has opened
        {
            if (real_board[i + k][j + l] == MINE) // checking if there is a mine in the 8 spaces
            {
                minecount++;
            }
        }
    }
    return minecount;
}

void initialise_board() // initialising board with '-'
{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            real_board[i][j] = player_board[i][j] = '-'; // initialising both player and normal board same
        }
    }
    cout << endl
         << "Welcome to Minesweeper!" << endl;

    place_mines(); // after initialising we called place_mines to randomly place mine in real_board
    for (int k = 0; k < lines; k++)
    {
        for (int l = 0; l < columns; l++)
        {
            if (real_board[k][l] != MINE)
            {
                real_board[k][l] = compute_neighbours(k, l) + '0'; // 0 is for cells that have no mines in neighborhood
            }
        }
    }
}
void print_board()
{
    cout << "      ";
    for (int i = 0; i < lines; i++)
    {
        cout << i << "    ";
    }
    cout << endl;
    cout << endl;
    for (int j = 0; j < lines; j++)
    {
        if (j < 10)
        {
            cout << j << "     ";
        }
        else
        {
            cout << j << "    ";
        }

        for (int k = 0; k < columns; k++)
        {
            if (k < 10)
            {
                cout << player_board[j][k] << "    ";
            }
            else
            {
                cout << player_board[j][k] << "     ";
            }
        }
        cout << endl;
    }
}

void replace_mine(int x, int y) // Find the first empty cell and put the mine from cell selected in first move in it

{
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (real_board[i][j] != MINE) // on first move if it coes out to be mine then it replaces with free cell
            {
                real_board[i][j] = MINE;
                real_board[x][y] = FREE_CELL;
            }
        }
    }
}

void uncover_board(int x, int y) // uncovering the 8 spacs around it.
{
    player_board[x][y] = real_board[x][y];
    if (real_board[x][y] == 0) // when real board has value 0 then it shud uncover the 8 spaces .

    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                player_board[x + i][y + j] = real_board[x + i][y + j];
            }
        }
    }
}

void play()
{
    int flags = mines;
    bool game_over = false;
    int total_moves = lines * columns - mines;
    int moves = 0;

    while (!game_over)
    {
        print_board();
        cout << flags << " Flags left" << endl;
        char z;
        cout << "Enter your move: " << endl;
        cout << "Enter Row: ";
        cin >> x;
        cout << "Enter column: ";
        cin >> y;
        cout << "Enter action: open(o)/flag(f): ";
        cin >> z;
        if (moves == 0) // for first move
        {
            if (is_mine(x, y)) // if there is mine
            {
                replace_mine(x, y); // replace that mine
            }
        }
        if (z == 'o') // selecting to open the cell
        {
            if (real_board[x][y] != MINE) // if not mine then
            {
                uncover_board(x, y); // call uncover function
                moves++;             // imp to increase the moves because it goes to the condition moves ==0 and whenever it finds the mine it replaces it .
            }
            if (moves == total_moves)
            {
                cout << endl
                     << "Game Over. You Won!." << endl;
                game_over = true;
            }
            else if (real_board[x][y] == MINE)
            {
                player_board[x][y] = MINE;
                cout << endl
                     << "Game Over. You Lost!" << endl;
                game_over = true;
            }
            else
            {
                if (player_board[x][y] == 'F')
                {
                    cout << endl
                         << "Cell is marked as flag. Press f to unflag the cell." << endl;
                }
                else
                {
                    cout << endl
                         << "Cell is a number." << endl;
                }
            }
        }
        if (z == 'f') // we chose a flag then
        {
            if (player_board[x][y] == FREE_CELL)
            {
                if (flags != 0) // no of flags remaining then
                {
                    player_board[x][y] = 'F'; // place f
                    flags--;                  // decreasing the count.
                }
                else
                {
                    cout << endl
                         << "Illegal Move! No Flags left." << endl;
                }
            }
            else if (player_board[x][y] == 'F') // already there is a flag then again if we put F then it becomes a free cell
            {
                player_board[x][y] = FREE_CELL;
                flags++; // flags number increased by 1
            }
            else
            {
                cout << endl
                     << "Illegal Move! Cell is a number." << endl;
            }
        }
    }
}

int main()
{
    difficulty_level();
    initialise_board();
    play();
}
