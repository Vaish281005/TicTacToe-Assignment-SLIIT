#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10  // Maximum board size

// Function to initialize the board with spaces
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            board[i][j] = ' ';
}

// Function to display the board
void displayBoard(char board[MAX_SIZE][MAX_SIZE], int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) printf("|");
        }
        printf("\n");
        if (i < size - 1) {
            for (int k = 0; k < size; k++) {
                printf("---");
                if (k < size - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

// Function to check if a move is valid
int isValidMove(char board[MAX_SIZE][MAX_SIZE], int size, int row, int col) {
    return row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ';
}

// Function to place a symbol on the board
void makeMove(char board[MAX_SIZE][MAX_SIZE], int row, int col, char symbol) {
    board[row][col] = symbol;
}

// Function to check for a winner
char checkWinner(char board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        char rowSymbol = board[i][0];
        int rowWin = (rowSymbol != ' ');
        for (int j = 1; j < size; j++)
            if (board[i][j] != rowSymbol) rowWin = 0;
        if (rowWin) return rowSymbol;

        char colSymbol = board[0][i];
        int colWin = (colSymbol != ' ');
        for (int j = 1; j < size; j++)
            if (board[j][i] != colSymbol) colWin = 0;
        if (colWin) return colSymbol;
    }

    char diagSymbol = board[0][0];
    int diagWin = (diagSymbol != ' ');
    for (int i = 1; i < size; i++)
        if (board[i][i] != diagSymbol) diagWin = 0;
    if (diagWin) return diagSymbol;

    char antiSymbol = board[0][size - 1];
    int antiWin = (antiSymbol != ' ');
    for (int i = 1; i < size; i++)
        if (board[i][size - 1 - i] != antiSymbol) antiWin = 0;
    if (antiWin) return antiSymbol;

    return ' ';
}

// Function to check for a draw
int isDraw(char board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

// Function to write the board state to a log file
void writeLog(FILE *logFile, char board[MAX_SIZE][MAX_SIZE], int size, int moveCount, char currentPlayer) {
    fprintf(logFile, "Move %d by Player %c:\n", moveCount, currentPlayer);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fprintf(logFile, " %c ", board[i][j]);
            if (j < size - 1) fprintf(logFile, "|");
        }
        fprintf(logFile, "\n");
        if (i < size - 1) {
            for (int k = 0; k < size; k++) {
                fprintf(logFile, "---");
                if (k < size - 1) fprintf(logFile, "+");
            }
            fprintf(logFile, "\n");
        }
    }
    fprintf(logFile, "\n");
}

// Function for computer to choose a random valid move
void getComputerMove(char board[MAX_SIZE][MAX_SIZE], int size, int *row, int *col) {
    do {
        *row = rand() % size;
        *col = rand() % size;
    } while (!isValidMove(board, size, *row, *col));
}

// Main function
int main() {
    int size, mode;
    printf("Enter board size (3 to 10): ");
    scanf("%d", &size);

    if (size < 3 || size > 10) {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Select mode:\n");
    printf("1. User vs User\n");
    printf("2. User vs Computer\n");
    printf("3. 3-Player Game\n");
    printf("Enter choice: ");
    scanf("%d", &mode);

    char board[MAX_SIZE][MAX_SIZE];
    initializeBoard(board, size);

    FILE *logFile = fopen("game_log.txt", "w");
    if (logFile == NULL) {
        printf("Error opening log file.\n");
        return 1;
    }

    srand(time(NULL));
    int moveCount = 0;
    char winner = ' ';
    int row, col;

    if (mode == 1) {
        // User vs User
        char currentPlayer = 'X';
        while (1) {
            displayBoard(board, size);
            printf("Player %c, enter row and column: ", currentPlayer);
            scanf("%d %d", &row, &col);

            if (!isValidMove(board, size, row, col)) {
                printf("Invalid move.\n");
                continue;
            }

            makeMove(board, row, col, currentPlayer);
            moveCount++;
            writeLog(logFile, board, size, moveCount, currentPlayer);

            winner = checkWinner(board, size);
            if (winner != ' ') {
                displayBoard(board, size);
                printf("Player %c wins!\n", winner);
                break;
            }

            if (isDraw(board, size)) {
                displayBoard(board, size);
                printf("It's a draw!\n");
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    } else if (mode == 2) {
        // User vs Computer
        char currentPlayer = 'X';
        while (1) {
            displayBoard(board, size);
            if (currentPlayer == 'X') {
                printf("Player X, enter row and column: ");
                scanf("%d %d", &row, &col);
                if (!isValidMove(board, size, row, col)) {
                    printf("Invalid move.\n");
                    continue;
                }
            } else {
                getComputerMove(board, size, &row, &col);
                printf("Computer chose: %d %d\n", row, col);
            }

            makeMove(board, row, col, currentPlayer);
            moveCount++;
            writeLog(logFile, board, size, moveCount, currentPlayer);

            winner = checkWinner(board, size);
            if (winner != ' ') {
                displayBoard(board, size);
                printf("Player %c wins!\n", winner);
                break;
            }

            if (isDraw(board, size)) {
                displayBoard(board, size);
                printf("It's a draw!\n");
                break;
            }

            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    } else if (mode == 3) {
        // 3-Player Game
        char players[3] = {'X', 'O', 'Z'};
        int turn = 0;
        while (1) {
            displayBoard(board, size);
            char currentPlayer = players[turn % 3];
            printf("Player %c, enter row and column: ", currentPlayer);
            scanf("%d %d", &row, &col);

            if (!isValidMove(board, size, row, col)) {
                printf("Invalid move.\n");
                continue;
            }

            makeMove(board, row, col, currentPlayer);
            moveCount++;
            writeLog(logFile, board, size, moveCount, currentPlayer);

            winner = checkWinner(board, size);
            if (winner != ' ') {
                displayBoard(board, size);
                printf("Player %c wins!\n", winner);
                break;
            }

            if (isDraw(board, size)) {
                displayBoard(board, size);
                printf("It's a draw!\n");
                break;
            }

            turn++;
        }
    } else {
        printf("Invalid mode selected.\n");
    }

    fclose(logFile);
    return 0;
}
