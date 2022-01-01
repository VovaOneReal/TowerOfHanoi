#include <stdio.h>
#include <locale.h>
#define SIZE 3


int row1[3] = { 3, 2, 1 };
int row2[3] = { 0, 0, 0 };
int row3[3] = { 0, 0, 0 };

void output_array(int* t) {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", t[i]);
	}
	printf("\n");
}

void move(int* from, int* to);
void draw(void);
int get_top_piece(int* t);
int check_condition(void);

int main(void) {
	setlocale(LC_ALL, "ru_RU");

	while (check_condition()) {
        draw();
        printf("Which row to get?\n");
        int choice = 0;
        scanf("%d", &choice);

        switch(choice){
        case 1:
            get_top_piece(row1);
            break;
        case 2:
            get_top_piece(row2);
            break;
        case 3:
            get_top_piece(row3);
            break;
        }
	}

	printf("You have solved the puzzle!");

	return 0;
}

int get_top_piece(int* t){
    int index;
    for (int i = 1; i <= SIZE; i++){
        int getted = t[SIZE-i];
        if (getted == 0) {
            continue;
        }
        else {
            index = SIZE-i;
            printf("Top index is %d\n", index);
            return index;
        }
    }
    return -1;
}

void move(int* from, int* to) {
	int top_circle = 0;
	for (int i = 0; i < 3; i++) {
		if (from[i] == 0) {
			top_circle = from[i];
		}
	}
}


void draw(void) {
	output_array(row1);
	output_array(row2);
	output_array(row3);
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
