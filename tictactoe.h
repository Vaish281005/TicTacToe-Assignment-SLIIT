#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>

#define MAX_SIZE 10

void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int size);
void displayBoard(char board[MAX_SIZE][MAX_SIZE], int size);
int isValidMove(char board[MAX_SIZE][MAX_SIZE], int size, int row, int col);
void makeMove(char board[MAX_SIZE][MAX_SIZE], int row, int col, char symbol);
char checkWinner(char board[MAX_SIZE][MAX_SIZE], int size);
int isDraw(char board[MAX_SIZE][MAX_SIZE], int size);
void writeLog(FILE *logFile, char board[MAX_SIZE][MAX_SIZE], int size, int moveCount, char currentPlayer);
void getComputerMove(char board[MAX_SIZE][MAX_SIZE], int size, int *row, int *col);

#endif
