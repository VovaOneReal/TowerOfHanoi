#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

// add counter of moves

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
	}

	system("cls");
	draw();
	printf("You have solved the puzzle!\n");

	return 0;
}

void move(int from, int to) {
	int* from_arr = get_array(from);
	int* to_arr = get_array(to);

	int value = pop_top(from_arr);
	put_on_top(to_arr, value);
}

void draw(void) {
	printf("\n");
	output_array(row1);
	output_array(row2);
	output_array(row3);
	printf("\n");
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
