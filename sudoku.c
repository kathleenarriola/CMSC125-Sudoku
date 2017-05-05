#include <stdio.h>
#define EASY 40
#define AVERAGE 30
#define DIFFICULT 20
#define SIZE 9

void randomize(int n) {
	while (n > 0) {

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

int checker(int answer[SIZE][SIZE]) {
	int i = 0;
	int j = 0;
	int hCheck[SIZE];
	int verticalCol[SIZE];
	int vertColIndex = 0;

	// horizontal
	for (i = 0; i < SIZE; i++) {
		if (lineCheck(answer[i]) == -1) {
			return -1;
		}
	}

	// vertical
	while (vertColIndex != SIZE) {
		for (i=0; i<SIZE; i++) {
			verticalCol[i] = answer[i][vertColIndex];
		}

		if (lineCheck(verticalCol) == -1) {
			return -1;
		}
		vertColIndex++;
	}

	return 1;
}

int main() {
	int board[SIZE][SIZE] = {
		{9, 4, 2, 7, 6, 1, 8, 5, 3},
		{3, 8, 7, 5, 9, 2, 6, 4, 1},
		{6, 1, 5, 8, 3, 4, 2, 9, 7},
		{2, 6, 3, 1, 4, 7, 5, 8, 9},
		{8, 7, 1, 9, 2, 5, 3, 6, 4},
		{4, 5, 9, 3, 8, 6, 1, 7, 2},
		{7, 9, 6, 2, 1, 8, 4, 3, 5},
		{, 2, 8, 4, 7, 3, 9, 1, 6},
		{1, 3, 4, 6, 5, 9, 7, 2, 8}
	};

	//int arr[] = {1, 2, 9, 3, 4, 5, 6, 7, 8};
	int ret = 0;

	ret = checker(board);
	printf("ret: %d\n", ret);

	return 0;
}