#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define ROW 9

typedef struct _Array
{
	short *arr;
	unsigned short size;
} Array;

void sudokoPrintBoard(short **sudoko_board)
{//prints sudoko board
	int i, j,k=0;
	printf("\n\n  | 0 1 2| 3 4 5| 6 7 8");
	for (i = 0; i < 9; i++)
	{
		printf("\n");
		if (i % 3 == 0)
			printf("-----------------------\n");
		printf(" %d", i);
		for (j = 0; j < 9; j++)
		{
			if (j % 3 == 0)
				printf("|");
			if ((*sudoko_board)[k] !=-1)
				printf(" %d", (*sudoko_board) [k]);
			else
				printf("  ");
			k++;
		}
	}
	printf("\n-----------------------\n\n\n");
}


void setTemp(Array *temp)
{//sets temp to check possibilities for a specific cell
	short i;
	temp->size = 9;
	temp->arr[0] = 0;
	for (i = 1; i < 10; i++)
		temp->arr[i] = i;
}

Array ***PossibleDigits(short **sudokuBoard)
{//allocates a possibilities pointer mattrix acording to a given sudoko board
	int i, j,k, row = 0, col = 0, row3x3, col3x3;
	Array temp;
	Array ***pos = (Array***)malloc(ROW * sizeof(Array**));
	for (i = 0; i < ROW; i++)
		pos[i] = (Array**)malloc(ROW * sizeof(Array*));
	temp.arr = (short*)malloc(10 * sizeof(short));
	setTemp(&temp);
	for (i = 0; i < 81; i++)
	{
		
		if ((*sudokuBoard)[i] != (-1))
			pos[row][col] = NULL;
		else
		{
			//finding row possibilities
			for (j = row * 9; j < (row * 9) + 9; j++)
			{
				if ((*sudokuBoard)[j] != (-1))
				{
					if (temp.arr[(*sudokuBoard)[j]] != 0)
					{
						temp.arr[(*sudokuBoard)[j]] = 0;
						temp.size--;
					}
				}
			}
			//finding collom possibilities
			for (j = col; j < col + 73; j += 9)
			{
				if ((*sudokuBoard)[j] != (-1))
				{
					if (temp.arr[(*sudokuBoard)[j]] != 0)
					{
						temp.arr[(*sudokuBoard)[j]] = 0;
						temp.size--;
					}
				}
			}
			//finding 3x3 possibilities
			if (row % 3 == 0)
				row3x3 = row;
			else if ((row - 1) % 3 == 0)
				row3x3 = row - 1;
			else if ((row - 2) % 3 == 0)
				row3x3 = row - 2;
			if (col % 3 == 0)
				col3x3 = col;
			else if ((col - 1) % 3 == 0)
				col3x3 = col - 1;
			else if ((col - 2) % 3 == 0)
				col3x3 = col - 2;
			for (j = col3x3+(row3x3*9); j < col3x3+(row3x3*9) + 21; j++)
			{
				if ((*sudokuBoard)[j] != (-1))
				{
					if (temp.arr[(*sudokuBoard)[j]] != 0)
					{
						temp.arr[(*sudokuBoard)[j]] = 0;
						temp.size--;
					}
				}
				if ((j + 1) % 3 == 0)
					j += 6;
			}
			pos[row][col] = (Array*)malloc(sizeof(Array));
			pos[row][col]->arr = (Array*)malloc(temp.size * sizeof(Array));
			pos[row][col]->size = temp.size;
			k = 0;
			for (j = 0; j < 10; j++)
				if (temp.arr[j] != 0)
				{
					pos[row][col]->arr[k] = j;
					k++;
				}
			setTemp(&temp);
		}
		col++;
		if (col == 9)
		{
			row++;
			col = 0;
		}
	}

	free(temp.arr);
	return pos;
}

int FillBoard(short **board, Array ***possibilities)
{//filling the sudoko board with 1 possibilities cells and gets from the user he's choises, output if the user won ot lost
	int i, j, k, row = 0, col = 0, row3x3, col3x3;
	int min_size=10,min_row,min_col,count_empty=0;
	char change = 'y', user_num = 'n';
	Array temp;
	temp.arr = (Array*)malloc(10 * sizeof(Array));
	setTemp(&temp);
	while (change == 'y')
	{
		change = 'n';
		row = 0;
		col = 0;
		//finding 1 possibilies and filling the spot
		for (i = 0; i < 81; i++)
		{
			if ((*board)[i] == (-1))
			{
				count_empty++;
				if ((*board)[i] == (-1) && possibilities[row][col]->size == 1)
				{
					(*board)[i] = possibilities[row][col]->arr[0];
					free(possibilities[row][col]);
					possibilities[row][col] = NULL;
					change = 'y';
				}
			}
			col++;
			if (col == 9)
			{
				row++;
				col = 0;
			}
		}
		if (count_empty == 0)
			return 0;
		count_empty = 0;
		col = 0;
		row = 0;
		//check new possibilities
		if (change == 'y'||user_num=='y')
		{
			change = 'y';
			user_num = 'n';
			for (i = 0; i < 81; i++)
			{
				if ((*board)[i] == (-1))
				{
					//finding row possibilities
					for (j = row * 9; j < (row * 9) + 9; j++)
					{
						if ((*board)[j] != (-1))
						{
							if (temp.arr[(*board)[j]] != 0)
							{
								temp.arr[(*board)[j]] = 0;
								temp.size--;
							}
						}
					}
					//finding collom possibilities
					for (j = col; j < col + 73; j += 9)
					{
						if ((*board)[j] != (-1))
						{
							if (temp.arr[(*board)[j]] != 0)
							{
								temp.arr[(*board)[j]] = 0;
								temp.size--;
							}
						}
					}
					//finding 3x3 possibilities
					if (row % 3 == 0)
						row3x3 = row;
					else if ((row - 1) % 3 == 0)
						row3x3 = row - 1;
					else if ((row - 2) % 3 == 0)
						row3x3 = row - 2;
					if (col % 3 == 0)
						col3x3 = col;
					else if ((col - 1) % 3 == 0)
						col3x3 = col - 1;
					else if ((col - 2) % 3 == 0)
						col3x3 = col - 2;
					for (j = col3x3 + (row3x3 * 9); j < col3x3 + (row3x3 * 9) + 21; j++)
					{
						if ((*board)[j] != (-1))
						{
							if (temp.arr[(*board)[j]] != 0)
							{
								temp.arr[(*board)[j]] = 0;
								temp.size--;
							}
						}
						if ((j + 1) % 3 == 0)
							j += 6;
					}

					possibilities[row][col]->arr=(Array*)calloc(temp.size, sizeof(Array));
					possibilities[row][col]->size = temp.size;
					k = 0;
					for (j = 0; j < 10; j++)
						if (temp.arr[j] != 0)
						{
							possibilities[row][col]->arr[k] = j;
							k++;
						}
					setTemp(&temp);
				}
				col++;
				if (col == 9)
				{
					row++;
					col = 0;
				}
				}
			col = 0;
			row = 0;
			
			}
		
		else
		{
			for(row=0;row<ROW;row++)
				for (col = 0; col < ROW; col++)
				{
					if(possibilities[row][col]!=NULL)
						if (possibilities[row][col]->size < min_size)
						{
							min_size = possibilities[row][col]->size;
							min_row = row;
							min_col = col;
						}
				}
			if (min_size == 0)
				return (-1);
			else
			{
				user_num = 'y';
				change = 'y';
				sudokoPrintBoard(board);
				printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", min_row, min_col);
				for (i = 1;i<=min_size; i++)
					printf("%d. %d\n", i, possibilities[min_row][min_col]->arr[i-1]);
				scanf_s("%d", &j);
				printf("Updating cell %d with value %d\n\n", ((min_row * 9) + min_col), j);
				(*board)[(min_row * 9) + min_col] =(short) j;
				free(possibilities[min_row][min_col]->arr);
				free(possibilities[min_row][min_col]);
				possibilities[min_row][min_col] = NULL;
			}
			row = 0;
			col = 0;
			min_size = 10;
		}
		}

		return 0;
}

void main()
{
	short board[81] = { 5,-1,4,-1,7,-1,-1,1,-1,6,-1,2,1,-1,-1,3,-1,-1,1,-1,8,-1,4,-1,-1,6,-1,-1,5,-1,-1,6,-1,-1,2,-1,-1,2,-1,8,-1,3,-1,-1,-1,-1,-1,-1,-1,-1,4,-1,5,6,-1,6,1,5,3,7,2,8,4,-1,8,7,-1,1,9,-1,3,-1,-1,-1,-1,2,8,-1,-1,-1,9 };
	short * sudoko_board = board;
	Array*** possible_solutions;

	printf("Initial board\n");
	sudokoPrintBoard(&sudoko_board);
	
	printf("Press enter to start playing...\n");
	getchar();

	possible_solutions = PossibleDigits(&sudoko_board);
	
	if (FillBoard(&sudoko_board, possible_solutions) == -1)
		printf("User's selections led to duplications\n");
	else
	{
		sudokoPrintBoard(&sudoko_board);
		printf("Board filled successfully\n");
	}

}
