#include <stdio.h>
#define EASY 40
#define AVERAGE 30
#define DIFFICULT 20
#define SIZE 9

void randomize(int n) {
	while (n > 0) {

	}
}

int checker(int * answer) {
	int i = 0;
	int j = 0;
	int hCheck[SIZE];

	// horizontal
	// for (i = 0; i < SIZE; i++) {
	// 	horizontalCheck(answer[i]);
	// }
}

int isPresent(int element, int * present, int presentLastIndex) {
	int i = 0;

	for (i = 0; i < presentLastIndex; i++) {
		if (present[i] == element) {
			return 1;
		}
	}

	return -1;
}

void clearPresent(int * present) {
	int i=0;

	for (i = 0; i < SIZE; i++) {
		present[i] = 0;
	}
}


int horizontalCheck(int row[SIZE]) {
	int i = 0;
	int ret = 0;
	int present[SIZE];
	int presentLastIndex = 0;

	// horizontal
	for (i = 0; i < SIZE; i++) {
		if (isPresent(row[i], present, presentLastIndex) == -1) {
			present[presentLastIndex] = row[i];
			presentLastIndex++;
		} else {
			return -1;
		}
	}

	clearPresent(present);
}

int main() {
	printf("Hello\n");
	int board[SIZE][SIZE];
	return 0;
}