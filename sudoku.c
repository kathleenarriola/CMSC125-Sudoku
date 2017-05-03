#include <stdio.h>
#define EASY 40
#define AVERAGE 30
#define DIFFICULT 20
#define SIZE 9

void randomize(int n) {
	while (n > 0) {

	}
}

int checker(int answer[SIZE][SIZE]) {
	int i = 0;
	int j = 0;
	int hCheck[SIZE];
	int verticalCol[SIZE];
	int vertColIndex = 0;

	// horizontal
	// for (i = 0; i < SIZE; i++) {
	// 	lineCheck(answer[i]);
	// }

	// vertical
	while (verticalColIndex != SIZE) {
		for (i=0; i<SIZE; i++) {
			verticalCol[i] = answer[i][vertColIndex];
		}
		lineCheck(verticalCol);
		verticalColIndex++;
	}
}

int isPresent(int element, int present[SIZE], int presentLastIndex) {
	int i = 0;

	for (i = 0; i < presentLastIndex; i++) {
		if (present[i] == element) {
			return 1;
		}
	}

	return -1;
}

int lineCheck(int row[SIZE]) {
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

	return 1;
}

int main() {
	printf("Hello\n");
	int board[SIZE][SIZE];
	int arr[] = {1, 2, 9, 3, 4, 5, 6, 7, 8};
	int ret = 0;

	ret = lineCheck(arr);
	printf("ret: %d\n", ret);

	return 0;
}