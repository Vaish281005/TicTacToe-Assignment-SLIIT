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

