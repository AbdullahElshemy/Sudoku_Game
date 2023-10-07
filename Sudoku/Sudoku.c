#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "Sudoku.h"


/*DEFINE Integer array function array as 9 by 9 two-dimensional array which stores numbers*/
int** createPuzzle()
{
    int i, j;
    int** puzzle;
    int arrayPuzzle[9][9] = { 9, 8, 7,   4, 0, 3,   5, 2, 6,
                              3, 1, 4,   2, 5, 6,   9, 7, 8,
                              2, 6, 5,   0, 0, 9,   4, 3, 1,

                              6, 4, 1,   9, 2, 8,   3, 5, 7,
                              7, 0, 3,   1, 6, 5,   8, 0, 2,
                              8, 5, 2,   0, 4, 7,   6, 1, 9,

                              5, 3, 8,   7, 9, 2,   1, 6, 4,
                              1, 2, 9,   6, 3, 4,   7, 8, 5,
                              0, 7, 6,   5, 8, 1,   2, 9, 3,
                            };

    /*ALLOCATE memory for Arr_puzzle*/
    puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++)
    {
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++)
        {
            puzzle[i][j] = arrayPuzzle[i][j];
        }
    }
    return puzzle;
}

/*printPuzzleas void function with int** puzzle Parameter*/
void printPuzzle(int** puzzle)
{
    int i, j, a;

    printf("\n");
    printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n");
    printf(" ---------------------------------\n");
    for (i = 0, a = 1; i < 9; i++, a++)
    {
        for(j = 0; j < 9; j++)
        {
            if (j == 0)
                printf(" %d |", a);
            else if ((j) % 3 == 0)
                printf("|");
            printf(" %d ", puzzle[i][j]);
            if (j == 8)
                printf("|");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf(" ---------------------------------\n");
    }
    printf(" Y\n");
}

/*checkAvailable as Bool function with parameters int** puzzle, int* row, int* column*/
int checkAvailable(int** puzzle, int* row, int* column)
{
    int i, j;

    for (i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if (puzzle[i][j] == 0)
            {
                *row = i;
                *column  = j;
                return 1;
            }
        }
    }

    return 0;
}

/*Check the values at coordinantes */
int checkBox(int** puzzle, int row, int column, int val)
{
    int i, j;
    int squareRow, squareColumn;

    //CHECK VERTICAL
    for(i = 0; i < 9; i++)
    {
        if (puzzle[i][column] == val)
            return 0;
    }

    //CHECK HORIZONTAL
    for(j = 0; j < 9; j++)
    {
        if (puzzle[row][j] == val)
            return 0;
    }

    //CHECK SQUARE
    squareRow = row - row % 3;
    squareColumn = column - column % 3;

    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(puzzle[squareRow + i][squareColumn + j] == val)
                return 0;
        }
    }

    return 1;
}


/*solvePuzzle as Bool function with parameter int** puzzle
CALL checkAvailable to see if there are empty squares in the puzzle
*/
int solvePuzzle(int** puzzle)
{
    int i, j, val;

    if(!checkAvailable(puzzle, &i, &j))
        return 1;

    for(val = 1; val < 10; val++)
    {
        if(checkBox(puzzle, i, j, val))
        {
            puzzle[i][j] = val;
            if(solvePuzzle(puzzle))
                return 1;
            else
                puzzle[i][j] = 0;
        }
    }
    return 0;
}

/*copy a new puzzle with a new values inserted*/
int** copyPuzzle(int** puzzle)
{
    int i, j;
    int** newPuzzle;

    newPuzzle = (int**)malloc(sizeof(int*) * 9);
    for (i = 0; i < 9; i++)
    {
        newPuzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++)
        {
            newPuzzle[i][j] = puzzle[i][j];
        }
    }
    return newPuzzle;
}

/*This Function prompts player for inputs and checks if inputs are valid and correct*/
void userChoice(int** userPuzzle, int** tempPuzzle)
{
    int i, j;
    int positionX, positionY, userVal;
    char c;

    while(1)
    {
        if(!checkAvailable(userPuzzle, &i, &j))
        {
            system("COLOR 0A");
            printf("\nGood Job You Solved the Puzzle!!!\n");
            printf("\t Congratulations\n\n");
            printf("Created by Abdullah-Elshemy\n");
            return;
        }

        while(1)
        {
            printf("\nPress Enter to continue. Press \"q\" to Quit.\n");
            c = getchar();
            if((c == 'q') || (c == 'Q'))
            {
                getchar();
                solvePuzzle(userPuzzle);
                printf("\nSOLVED PUZZLE:\n");
                printPuzzle(userPuzzle);
                return;
            }
            else if((c != '\n') && (c != 'q'))
                getchar();
            else
                break;
        }


        printf("\nplease Enter Coordinate for the square you want to insert the value to in the following format \"X Y\":\n");
        scanf("%d %d",&positionX, &positionY);
        while(1)
        {
            if ((positionX > 9) || (positionX < 1) || (positionY > 9) || (positionY < 1) || (userPuzzle[positionY - 1][positionX - 1] != 0))
            {
                Beep(900,900);
                system("COLOR 04");
                printf("\nyou can't insert value to this Coordinate, please pick a new Coordinate\n");
                scanf("%d %d",&positionX, &positionY);
            }
            else
            {
                positionX -= 1;
                positionY -= 1;
                break;
            }
        }


        printf("\nPlease insert value from 1 to 9\n");
        scanf("%d", &userVal);
        while(1)
        {
            if((userVal > 9) || (userVal < 1))
            {
                printf("\nplease insert valid value:\n");
                scanf("%d", &userVal);
            }
            else break;
        }

        if(checkBox(userPuzzle, positionY, positionX, userVal))
            userPuzzle[positionY][positionX] = userVal;
        else
            printf("\nincorrect value for the X = %d Y = %d coordinate, please try again\n",positionX + 1, positionY + 1);

        for (i = 0; i < 9; i++)
        {
            for(j = 0; j < 9; j++)
            {
                tempPuzzle[i][j] = userPuzzle[i][j];
            }
        }

        if(!solvePuzzle(tempPuzzle))
        {
            printf("\nincorrect value for the X = %d Y = %d coordinate, please try again\n",positionX + 1, positionY + 1);
            userPuzzle[positionY][positionX] = 0;
        }
        getchar();
        printPuzzle(userPuzzle);
    }

    return;
}
