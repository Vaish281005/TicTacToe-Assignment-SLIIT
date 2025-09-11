#include <stdio.h>
#include <stdlib.h>

#define MIN 3
#define MAX 10

void initBoard(char **board, int size);
void printBoard(char **board, int size);
int validMove(char **board, int r, int c, int size);
int checkWin(char **board, int size, char symbol);
int checkDraw(char **board, int size);
void logMove(FILE *fp, int r, int c, char symbol);

int main() {
	int size;
	printf("Enter board size (%d-%d): ", MIN, MAX);
	scanf("%d", &size);

	if (size < MIN || size > MAX) {
		printf("Invalid size. \n");
		return 1;
	}

	char **board = malloc(size * sizeof(char *));
	for (int i = 0; i < size; i++)
		board[i] = malloc(size * sizeof(char));

	initBoard(board, size);

	FILE *fp = fopen("moves.txt", "w");
	if (!fp) {
		printf("File error. \n");
		return 1;
	}

	char players[2] = {'X', 'O'};
	int turn = 0, row, col;

	while (1) {
		printBoard(board, size);
		printf("Player %c - Enter row and col: ", players[turn]);
		scanf("%d %d", &row, &col);

		if (!validMove(board, row, col, size)) {
			printf("Invalid move. Try again. \n");
			continue;
		}

		board[row][col] = players[turn];
		logMove(fp, row, col, players[turn]);

		if (checkWin(board, size, players[turn])) {
		   printBoard(board, size);
		   printf("Player %c wins! \n", players[turn]);
		   break;
		}

		if (checkDraw(board, size)) {
			printBoard(board, size);
			printf("Draw! \n");
			break;
		}

		turn = 1 - turn;
	}

	fclose(fp);
	for (int i = 0;  i < size; i++)
		free(board[i]);
	free(board);

	return 0;
}

#include <stdio.h>
void initBoard(char **board, int size) {
	for (int i =0; i < size; i++)
		for (int j = 0; j < size; j++)
			board[i][j] = '-';
}

void printBoard(char **board, int size) {
	printf("\n");
	for (int i = 0; i < size; i++) {
		for (int j =0; j < size; j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
	printf("\n");
}

int validMove(char **board, int r, int c, int size) {
	return r >= 0 && r < size && c >= 0 && c < size && board[r][c] == '-';
}

int checkWin(char **board, int size, char symbol) {
	int win;

	for (int i = 0; i < size; i++) {
		win = 1;
		for (int j =0; j < size; j++)
			if (board[i][j] != symbol) win = 0;
		if (win) return 1;
	

	win = 1;
	for (int j = 0; j < size; j++)
		if (board[j][i] != symbol) win = 0;
	if (win) return 1;

}

win = 1;
for (int i = 0;  i < size; i++)
    if (board[i][i] != symbol) win = 0;
if (win) return 1;

win = 1;
for (int i =0; i < size; i++)
    if (board[i][size - i -1] != symbol) win = 0;
if (win) return 1;

return 0;
}

int checkDraw(char **board, int size) {
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (board[i][j] == '-') return 0;
	return 1;
}

void logMove(FILE *fp, int r, int c, char symbol) {
	fprintf(fp, "Player %c: (%d, %d)\n", symbol, r, c);
}
