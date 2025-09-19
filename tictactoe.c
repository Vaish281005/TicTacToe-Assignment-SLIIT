#include <stdio.h>
#include <stdlib.h>

#define MIN 3
#define MAX 10

// Function declaration
void initBoard(char *board, int size);
void printBoard(char *board, int size);
int isValidMove(char *board, int r, int c, int size);
int checkWin(char *board, int size, char symbol);
int checkDraw(char *board, int size);
void logMove(FILE *fp, int r, int c, char symbol);

int main() {
    int size;

    // Ask user for board size
    printf("Enter board size (%d-%d): ", MIN, MAX);
    scanf("%d", &size);

    // Validate board size
    if (size < MIN || size > MAX) {
        printf("Invalid board size.\n");
        return 1;
    }


    // Allocate memory for 1D board
    char *board = malloc(size * size * sizeof(char));
    if (board == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    initBoard(board, size); // Fill board with '-'

    // Open file to log moves
    FILE *fp = fopen("moves.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        free(board);
        return 1;
    }

    char players[2] = {'X', 'O'};
    int turn = 0, row, col;

    // Main game loop
    while (1) {
        printBoard(board, size); // Show current board

	// Ask current player for move
        printf("Player %c - Enter row and column: ", players[turn]);
        scanf("%d %d", &row, &col);

	// Check if move is valid
        if (!isValidMove(board, row, col, size)) {
            printf("Invalid move. Try again.\n");
            continue;
        }

	// Update board and log move
        board[row * size + col] = players[turn];
        logMove(fp, row, col, players[turn]);

	// Check for win
        if (checkWin(board, size, players[turn])) {
            printBoard(board, size);
            printf("Player %c wins!\n", players[turn]);
            break;
        }


	// Check for draw
        if (checkDraw(board, size)) {
            printBoard(board, size);
            printf("Game is a draw.\n");
            break;
        }

	// Switch turn
        turn = 1 - turn;
    }

    fclose(fp);
    free(board);
    return 0;
}

#include <stdio.h>

// Initialize board with '-'
void initBoard(char *board, int size) {
    for (int i = 0; i < size * size; i++)
        board[i] = '-';
}

// Print the board in grid format
void printBoard(char *board, int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf(" %c ", board[i * size + j]);
        printf("\n");
    }
    printf("\n");
}

// Check if move is inside bounds and cell is empty
int isValidMove(char *board, int r, int c, int size) {
    if (r < 0 || r >= size || c < 0 || c >= size)
        return 0;
    return board[r * size + c] == '-';
}

// Check if player has won
int checkWin(char *board, int size, char symbol) {
    int win;

    // Check rows
    for (int i = 0; i < size; i++) {
        win = 1;
        for (int j = 0; j < size; j++)
            if (board[i * size + j] != symbol) win = 0;
        if (win) return 1;
    }

    // Check columns
    for (int j = 0; j < size; j++) {
        win = 1;
        for (int i = 0; i < size; i++)
            if (board[i * size + j] != symbol) win = 0;
        if (win) return 1;
    }

    // Check main  diagonal
    win = 1;
    for (int i = 0; i < size; i++)
        if (board[i * size + i] != symbol) win = 0;
    if (win) return 1;

    // Check anti-diagonal
    win = 1;
    for (int i = 0; i < size; i++)
        if (board[i * size + (size - i - 1)] != symbol) win = 0;
    if (win) return 1;

    return 0;
}

// Check if board is full (draw)
int checkDraw(char *board, int size) {
    for (int i = 0; i < size * size; i++)
        if (board[i] == '-') return 0;
    return 1;
}

// Write move to file
void logMove(FILE *fp, int r, int c, char symbol) {
    fprintf(fp, "Player %c: (%d, %d)\n", symbol, r, c);
}
