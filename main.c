#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int row;
	int col;
} Coordinate;

int* getPossibleNumbers(char field[9][9], Coordinate cur)
{
	int *pos = malloc(sizeof(int) * 9);
	for (char i = 0; i<9; i++)
		pos[i] = 1;
	// row
	for (char i = 0; i < 9; i++)
	{
		if (field[cur.row][i]) pos[(field[cur.row][i])-1] = 0;
	}
	// col
	for (char i = 0; i < 9; i++)
	{
		if (field[i][cur.col]) pos[(field[i][cur.col])-1] = 0;
	}
	// // square
	const int squareCols = cur.col / 3;
	const int squareRows = cur.row / 3;
	for (char i = 0; i < 3; i++)
	{
		if (field[(squareRows*3)+i][(squareCols*3) + 0]) pos[field[(squareRows*3)+i][(squareCols*3) + 0] - 1] = 0;
		if (field[(squareRows*3)+i][(squareCols*3) + 1]) pos[field[(squareRows*3)+i][(squareCols*3) + 1] - 1] = 0;
		if (field[(squareRows*3)+i][(squareCols*3) + 2]) pos[field[(squareRows*3)+i][(squareCols*3) + 2] - 1] = 0;
	}

	return pos;
}


Coordinate nextFreeCell(char field[9][9], Coordinate cur)
{
	Coordinate next = {-1, -1};

	for (char i = 0; i < 9; i++)
	{
		for (char j = 0; j < 9; j++)
		{
			if (!field[i][j])
			{
				next.row = i;
				next.col = j;
			}
		}
	}

	return next;
}

bool solve(char field[][9], Coordinate cur)
{
	// ist schon gesetzt -> weiter machen
	if (field[cur.row][cur.col]) return true;
	
	// ist noch nicht gesetzt -> welche zahlen sind möglich
	int *pos = getPossibleNumbers(field, cur);
	// f+ge alle mögl. zahlen in Array und gehe sie nacheinander durch
	for (char i = 0; i < 9; i++) 
	{
		if (! *(pos + i)) continue;

		int tmp = field[cur.row][cur.col];
		field[cur.row][cur.col] = (*(pos + i)) * (i+1);
		
	// wenn keine Zahl mehr "0" (sprich frei) ist, gebe `true` zurück
		const Coordinate next = nextFreeCell(field, cur);
		if (next.row == -1 && next.col == -1) return true;
		if (solve(field, next)) return true;
		field[cur.row][cur.col] = tmp;
	}
	free(pos);
	// wenn keine Zahl möglich ist, gebe `false zurück`
	return false;
}

int main(void)
{
	// char field[][9] = {
	// 	{2,1,3,0,5,7,9,0,0},
	// 	{0,0,5,0,0,0,3,8,0},
	// 	{0,0,0,3,1,0,0,5,0},
	// 	{3,0,2,9,0,0,6,1,7},
	// 	{9,0,7,2,0,0,0,0,0},
	// 	{4,0,0,0,0,5,0,2,0},
	// 	{0,3,4,5,8,9,2,0,6},
	// 	{0,2,6,0,7,0,0,9,0},
	// 	{0,0,8,6,0,4,1,0,5},
	// };
	char field[][9] = {
		{0,0,0,2,0,0,0,0,0},
		{0,0,4,1,0,0,0,0,8},
		{0,8,3,0,0,0,2,0,0},
		{0,3,0,0,0,0,7,0,0},
		{2,0,0,5,1,8,0,0,9},
		{0,0,5,0,0,0,0,4,0},
		{0,0,9,0,0,0,6,2,0},
		{7,0,0,0,0,5,4,0,0},
		{0,0,0,0,6,1,0,0,0},
	};
	
	Coordinate start = nextFreeCell(field, (Coordinate){0,0});

	printf("success? %B\n", solve(field, start ));

	for (char i = 0; i < 9; i++)
	{
		for (char j = 0; j < 9; j++)
		{
			printf("%i ", field[i][j]);
		}
		printf("\n");
	}

	return 0;
}
