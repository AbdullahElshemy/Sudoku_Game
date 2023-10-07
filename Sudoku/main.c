#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <dos.h>
#include "Sudoku.h"



void main()
{
    /*we just call these Functions and assign them to variables*/
    int** puzzle = createPuzzle();
    int** userPuzzle = copyPuzzle(puzzle);
    int** tempPuzzle = copyPuzzle(puzzle);
    system("COLOR 0B");
    printf("Rules Of Game:\n\n");
    printf("1. The objective of Sudoku is to fill a 9x9 grid made of small squares so that each row, each column, and each full 3x3 squares use the numbers 1-9.\n");
    printf("2. While solving the sudoku puzzle you can only use each number one time in the square, column, and row.\n");
    printf("3. You can only insert numbers in the squares that have value \"0\"\n");
    printf("4. If you give up and want to see a solved puzzle please press \"q\" key.\n\n");
    printf("Let's Start!\n");
    printPuzzle(userPuzzle);
    userChoice(userPuzzle,tempPuzzle);
    free(puzzle);
    free(userPuzzle);
    free(tempPuzzle);


    //Sleep(100);





}
