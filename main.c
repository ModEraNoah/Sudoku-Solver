#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int row;
	int col;
} Coordinate;

char* getPossibleNumbers(char field[9][9], Coordinate cur)
{
	char *pos = malloc(sizeof(char) * 9);
	char t[] = {1,1,1,1,1,1,1,1,1};
	pos = t;
	// row
	for (char i = 0; i < 9; i++)
	{
		if (field[cur.row][i]) pos[field[cur.row][i]] = 0;
	}
	// col
	for (char i = 0; i < 9; i++)
	{
		if (field[i][cur.col]) pos[field[i][cur.col]] = 0;
	}
	// square
	const char squareCols = cur.col / 3;
	const char squareRows = cur.row / 3;
	for (char i = 0; i < 3; i++)
	{
		if (field[squareRows+i][squareCols + 0]) pos[field[squareRows+i][squareCols + 0]] = 0;
		if (field[squareRows+i][squareCols + 1]) pos[field[squareRows+i][squareCols + 0]] = 0;
		if (field[squareRows+i][squareCols + 2]) pos[field[squareRows+i][squareCols + 2]] = 0;
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
	char *pos = getPossibleNumbers(field, cur);
	// f+ge alle mögl. zahlen in Array und gehe sie nacheinander durch
	for (char i = 0; i < 9; i++) 
	{
		printf("current possible number: %i\n", *(pos + i));
		if (! *(pos + i)) continue;

		int tmp = field[cur.row][cur.col];
		field[cur.row][cur.col] = *(pos + i);
		
	// wenn keine Zahl mehr "0" (sprich frei) ist, gebe `true` zurück
		const Coordinate next = nextFreeCell(field, cur);
		if (next.row == -1 && next.col == -1) return true;
		solve(field, next);

		field[cur.row][cur.col] = tmp;
	}
	// wenn keine Zahl möglich ist, gebe `false zurück`

	return false;
}

int main(void)
{
	char field[][9] = {
		{0,0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,9,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,5,0,0,0,4,0,0},
		{0,0,0,0,0,0,0,0,0},
	};

	solve(field, (Coordinate) {0,0});

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
