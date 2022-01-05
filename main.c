#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 3
#define SPACE 32
#define BG_BLOCK 176
#define STICK 177
#define PIECE 178
#define FLOOR_BLOCK 219
#define PEAKS -1
#define FLOOR -2
#define BACKGROUND -3
#define LABELS -4

// add protection from incorrecct input
// make the height of the tower scalable

int row1[3] = { 3, 2, 1 };
int row2[3] = { 0, 0, 0 };
int row3[3] = { 0, 0, 0 };

void output_array(int* t) {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", t[i]);
	}
	printf("\n");
}

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

	int moves = 0;

	while (check_condition()) {
		system("cls");
        draw();

		int get_from, put_on;

		while (check_is_empty(get_from = get_from_row())) {
			system("cls");
			draw();
			printf("This row is empty! Choose another one.\n\n");
			continue;
		}	
		while (check_puttable(get_from, put_on = put_to_row())) {
			system("cls");
			draw();
			printf("You can put pieces only on ones which are bigger!\n\n");
		}

		move(get_from, put_on);
		moves++;
	}

	system("cls");
	draw();
	printf("You have solved the puzzle!\n");
	printf("You have done it for %d moves.\n", moves);

	int optimal = (int) pow(2, SIZE) - 1;
	if (moves > optimal) {
		printf("But the puzzle could be solved for %d moves!", optimal);
	}
	else {
		printf("You solved the puzzle brilliantly!");
	}

	return 0;
}

void move(int from, int to) {
	int* from_arr = get_array(from);
	int* to_arr = get_array(to);

	int value = pop_top(from_arr);
	put_on_top(to_arr, value);
}

void draw_symbols(int code, int amount) {
	char c = code;
	for (int i = 0; i < amount; i++) {
		printf("%c", c);
	}
}

void draw_rows(int value) {
	if (value == 0) {
		draw_symbols(BG_BLOCK, 19);
		draw_symbols(STICK, 2);
		draw_symbols(BG_BLOCK, 19);
	}
	else if (value == 1) {
		draw_symbols(BG_BLOCK, 14);
		draw_symbols(PIECE, 12);
		draw_symbols(BG_BLOCK, 14);
	}
	else if (value == 2) {
		draw_symbols(BG_BLOCK, 8);
		draw_symbols(PIECE, 24);
		draw_symbols(BG_BLOCK, 8);
	}
	else if (value == 3) {
		draw_symbols(BG_BLOCK, 2);
		draw_symbols(PIECE, 36);
		draw_symbols(BG_BLOCK, 2);
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

	for (int h = SIZE - 1; h >= 0; h--) {
		for (int i = 0; i < 2; i++) {
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
	scanf("%d", &choice);
	return choice;
}

int put_to_row(void)
{
	printf("To which row to put?\n");
	int choice;
	scanf("%d", &choice);
	return choice;
}

int check_is_empty(int index)
{
	int* arr = get_array(index);
	for (int i = 0; i < SIZE; i++) {
		if (arr[i] > 0) {
			return 0;
		}
	}
	return 1;
}

int check_puttable(int from, int to) {
	int* from_arr = get_array(from);
	int* to_arr = get_array(to);
	int from_value, to_value;

	from_value = get_top(from_arr);
	to_value = get_top(to_arr);

	if (from_value < to_value) {
		return 0;
	}
	else {
		return 1;
	}
}

int get_top(int* t)
{
	int index;
	for (int i = 1; i <= SIZE; i++) {
		index = SIZE - i;
		if (t[index] == 0) {
			continue;
		}
		else {
			return t[index];
		}
	}
	return 4;
}

int pop_top(int* t)
{
	int index;
	int value = 0;
	for (int i = 1; i <= SIZE; i++) {
		index = SIZE - i;
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
	for (int i = 0; i < SIZE; i++) {
		if (t[i] == 0) {
			t[i] = value;
			break;
		}
	}
}

int check_condition(void) {
	int win_row[SIZE] = { 3, 2, 1 };
	int success = 0;
	for (int i = 0; i < SIZE; i++) {
		if (row3[i] == win_row[i]) {
			success += 1;
		}
	}

	if (success == 3) {
		return 0;
	}

	return 1;
}
