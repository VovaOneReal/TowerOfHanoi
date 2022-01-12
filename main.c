#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SPACE 32
#define BG_BLOCK 176
#define STICK 177
#define PIECE 178
#define FLOOR_BLOCK 219

#define PEAKS -1
#define FLOOR -2
#define BACKGROUND -3
#define LABELS -4

// TO-DO
// -----
// code review and refactoring. Someday...
// 
// ADDITIONAL FEAUTURES
// make rows and their data as 2D array
// fix bed english

int* row1;
int* row2;
int* row3;
int* win_row;
int height = 0;
int get_from, put_on;
int moves = 0;
int is_after_wrong_move = 0;

void output_array(int* t) {
	for (int i = 0; i < height; i++) {
		printf("%d ", t[i]);
	}
	printf("\n");
}

void menu(void);
void init_tower(void);
int play_again(void);
void clear_data(void);

void free_bufer(void);

void move(int from, int to);

void draw_symbols(int code, int amount);
void draw_rows(int value);
void draw(void);

int* get_array(int index);
int get_from_row(void);
int put_to_row(void);
int check_is_empty(int index);
int check_puttable(int from, int to);

int get_top(int* t);
int pop_top(int* t);
void put_on_top(int* t, int value);
int check_condition(void);

int main(void) {

	do {
		system("cls");
		clear_data();
		menu();
		init_tower();

		while (check_condition()) {
			system("cls");
			draw();

			//output_array(row1);
			//output_array(row2);
			//output_array(row3);

			while (check_is_empty(get_from = get_from_row())) {
				system("cls");
				draw();
				printf("This row is empty! Choose another one.\n\n");
				continue;
			}
			printf("\n");
			while (check_puttable(get_from, put_on = put_to_row())) {
				system("cls");
				draw();
				printf("You can put pieces only on ones which are bigger!\n\n");
				printf("You've chosen the Row %d.\n", get_from);
			}

			move(get_from, put_on);
		}

		system("cls");
		draw();
		printf("You have solved the puzzle!\n\n");
		printf("You have done it for %d moves.\n", moves);

		int optimal = (int)pow(2, height) - 1;
		if (moves > optimal) {
			printf("But the puzzle could be solved for %d moves!\n\n", optimal);
		}
		else {
			printf("You solved the puzzle brilliantly!\n\n");
		}
	} while (play_again());

	printf("\nGoodbye!\n");
	printf("------------------------------------\n");
	printf("Author: Vladimir Tolstunov (VovaOne)\nVersion 1.0 | January 2022\n\n");

	system("pause");

	return 0;
}

void menu(void) {
	printf("     ______   ______     __     __     ______     ______\n");
	printf("    /\\__  _\\ /\\  __ \\   /\\ \\  _ \\ \\   /\\  ___\\   /\\  == \\\n");
	printf("    \\/_/\\ \\/ \\ \\ \\/\\ \\  \\ \\ \\/ \".\\ \\  \\ \\  __\\   \\ \\  __< \n");
	printf("       \\ \\_\\  \\ \\_____\\  \\ \\__/\".~\\_\\  \\ \\_____\\  \\ \\_\\ \\_\\\n");
	printf("        \\/_/   \\/_____/   \\/_/   \\/_/   \\/_____/   \\/_/ /_/\n");
	printf("\n");
	printf("                          ______     ______\n");
	printf("                         /\\  __ \\   /\\  ___\\\n");
	printf("                         \\ \\ \\/\\ \\  \\ \\  __\\\n");
	printf("                          \\ \\_____\\  \\ \\_\\\n");
	printf("                           \\/_____/   \\/_/\n");
	printf("\n");
	printf("              __  __     ______     __   __     ______     __\n");
	printf("             /\\ \\_\\ \\   /\\  __ \\   /\\ \"-.\\ \\   /\\  __ \\   /\\ \\\n");
	printf("             \\ \\  __ \\  \\ \\  __ \\  \\ \\ \\-.  \\  \\ \\ \\/\\ \\  \\ \\ \\\n");
	printf("              \\ \\_\\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\  \\ \\_\\\n");
	printf("               \\/_/\\/_/   \\/_/\\/_/   \\/_/ \\/_/   \\/_____/   \\/_/\n");
	printf("\n");

	printf("Tower of Hanoi is a popular puzzle game. Three rods are given. \nOne of them has a pyramid-shaped disk stacked on it.\n\n");
	printf("Your goal is to move the tower from the left rod to the right.\n\n");
	printf("Moving rules: \n1) you can move only one disc at a time; \n2) to move, you take only the top disc on the rod; \n3) you cannot place a larger disc on a smaller disc.\n\n");

	printf("To start solving the puzzle, enter the height of the tower (19 - max): ");
	while (scanf("%d", &height) != 1) {
		free_bufer();
	}

	if (height > 19) {
		height = 19;
	}
	else if (height < 1) {
		height = 1;
	}
}

void init_tower(void) {
	row1 = (int*)malloc(height * sizeof(int));
	row2 = (int*)malloc(height * sizeof(int));
	row3 = (int*)malloc(height * sizeof(int));
	win_row = (int*)malloc(height * sizeof(int));

	for (int h = height, i = 0; h > 0; h--, i++) {
		row1[i] = h;
		win_row[i] = h;
		
		row2[i] = 0;
		row3[i] = 0;
	}
}

int play_again(void) {
	printf("Exit the game?\n(1 - yes, 2 - no)\n");
	int choice = 0;
	while (scanf("%d", &choice) != 1) {
		free_bufer();
	}
	if (choice == 1) {
		return 0;
	}
	return 1;
}

void clear_data(void) {
	row1 = NULL;
	row2 = NULL;
	row3 = NULL;
	win_row = NULL;
	height = 0;
	get_from = 0;
	put_on = 0;
	moves = 0;
	is_after_wrong_move = 0;
}

void move(int from, int to) {
	int* from_arr = get_array(from);
	int* to_arr = get_array(to);

	int value = pop_top(from_arr);
	put_on_top(to_arr, value);
	
	if (from != to) {
		moves++;
	}
}

void draw_symbols(int code, int amount) {
	char c = code;
	for (int i = 0; i < amount; i++) {
		printf("%c", c);
	}
}

void draw_rows(int value) {
	int centerer = 0;
	int block_amount = 0;

	if (value == 0) {
		draw_symbols(BG_BLOCK, 19);
		draw_symbols(STICK, 2);
		draw_symbols(BG_BLOCK, 19);
	}
	else if (value >= 0) {
		if (value == height) {
			block_amount = 38;
		}
		else {
			int add = 38 / height;
			block_amount = value * add;
			if (block_amount % 2 != 0) {
				block_amount++;
			}
		}
		
		centerer = (40 - block_amount) / 2;

		draw_symbols(BG_BLOCK, centerer);

		if (!is_after_wrong_move) {
			draw_symbols(PIECE, block_amount);
		}
		else {
			int separated_block_amount = (block_amount - 2) / 2;

			draw_symbols(PIECE, separated_block_amount);
			if (value < 10) {
				printf("0");
				printf("%d", value);
			}
			else {
				printf("%d", value);
			}
			draw_symbols(PIECE, separated_block_amount);
		}
		draw_symbols(BG_BLOCK, centerer);
	}
	else if (value == PEAKS) {
		draw_symbols(BG_BLOCK, 19);
		draw_symbols(STICK, 2);
		draw_symbols(BG_BLOCK, 19);
		draw_symbols(BG_BLOCK, 19);
		draw_symbols(STICK, 2);
		draw_symbols(BG_BLOCK, 19);
		draw_symbols(BG_BLOCK, 19);
		draw_symbols(STICK, 2);
		draw_symbols(BG_BLOCK, 19);
	}
	else if (value == FLOOR) {
		draw_symbols(FLOOR_BLOCK, 120);
	}
	else if (value == BACKGROUND) {
		draw_symbols(BG_BLOCK, 120);
	}
	else if (value == LABELS) {
		draw_symbols(PIECE, 9);

		draw_symbols(STICK, 5);
		draw_symbols(BG_BLOCK, 3);
		draw_symbols(SPACE, 1);
		printf("Row 1");
		draw_symbols(SPACE, 1);
		draw_symbols(BG_BLOCK, 3);
		draw_symbols(STICK, 5);

		draw_symbols(PIECE, 17);

		draw_symbols(STICK, 5);
		draw_symbols(BG_BLOCK, 3);
		draw_symbols(SPACE, 1);
		printf("Row 2");
		draw_symbols(SPACE, 1);
		draw_symbols(BG_BLOCK, 3);
		draw_symbols(STICK, 5);

		draw_symbols(PIECE, 17);

		draw_symbols(STICK, 5);
		draw_symbols(BG_BLOCK, 3);
		draw_symbols(SPACE, 1);
		printf("Row 3");
		draw_symbols(SPACE, 1);
		draw_symbols(BG_BLOCK, 3);
		draw_symbols(STICK, 5);

		draw_symbols(PIECE, 8);
	}
	else if (value == LABELS) {
		draw_symbols(PIECE, 18);
		printf("Row 1");
		draw_symbols(PIECE, 35);
		printf("Row 2");
		draw_symbols(PIECE, 35);
		printf("Row 3");
		draw_symbols(PIECE, 17);
	}
}

void draw(void) {
	
	draw_rows(BACKGROUND);
	draw_rows(PEAKS);

	for (int h = height - 1; h >= 0; h--) {
		for (int i = 0; i < 1; i++) {
			draw_rows(row1[h]);
			draw_rows(row2[h]);
			draw_rows(row3[h]);
		}
	}

	draw_rows(FLOOR);
	draw_rows(LABELS);
	draw_rows(FLOOR);
	printf("\n\n");
}

int* get_array(int index)
{
	switch (index)
	{
	case 1:
		return row1;
	case 2:
		return row2;
	case 3:
		return row3;
	default:
		break;
	}
	return NULL;
}

int get_from_row(void)
{
	printf("From which row to get?\n");
	int choice;
	while (scanf("%d", &choice) != 1) {
		free_bufer();
	}
	if (choice > 3) {
		choice = 3;
	}
	else if (choice < 1) {
		choice = 1;
	}
	return choice;
}

int put_to_row(void)
{
	printf("To which row to put?\n");
	int choice;
	while (scanf("%d", &choice) != 1) {
		free_bufer();
	}
	if (choice > 3) {
		choice = 3;
	}
	else if (choice < 1) {
		choice = 1;
	}
	return choice;
}

int check_is_empty(int index)
{
	int* arr = get_array(index);
	for (int i = 0; i < height; i++) {
		if (arr[i] > 0) {
			return 0;
		}
	}
	return 1;
}

int check_puttable(int from, int to) {
	if (to == from) {
		return 0;
	}

	int* from_arr = get_array(from);
	int* to_arr = get_array(to);
	int from_value, to_value;

	from_value = get_top(from_arr);
	to_value = get_top(to_arr);

	if (from_value < to_value) {
		is_after_wrong_move = 0;
		return 0;
	}
	else {
		is_after_wrong_move = 1;
		return 1;
	}
}

int get_top(int* t)
{
	int index;
	for (int i = 1; i <= height; i++) {
		index = height - i;
		if (t[index] == 0) {
			continue;
		}
		else {
			return t[index];
		}
	}
	return height+1;
}

int pop_top(int* t)
{
	int index;
	int value = 0;
	for (int i = 1; i <= height; i++) {
		index = height - i;
		int getted = t[index];
		if (getted == 0) {
			continue;
		}
		else {
			value = t[index];
			t[index] = 0;
			return value;
		}
	}
	return value;
}

void put_on_top(int* t, int value)
{
	for (int i = 0; i < height; i++) {
		if (t[i] == 0) {
			t[i] = value;
			break;
		}
	}
}

int check_condition(void) {
	int success = 0;
	for (int i = 0; i < height; i++) {
		if (row3[i] == win_row[i]) {
			success += 1;
		}
	}

	if (success == height) {
		return 0;
	}

	return 1;
}

void free_bufer(void) {
	while (getchar() != '\n') {
		continue;
	}
}