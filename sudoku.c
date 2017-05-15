/*
    Sudoku Game for ICS-OS
    Kathleen Arriola
    Anna-Mae Fernandez
*/

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"

/* constants */
#define EASY 40
#define MEDIUM 30
#define HARD 20
#define SIZE 9

#define BLACK 100
#define WHITE 63

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

#define QUIT 'x'
#define BACK 'b'
#define SUBMIT 'g'

#define EASY_ROUND 'e'
#define MEDIUM_ROUND 'm'
#define HARD_ROUND 'h'

#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9

/* global variables */
int board[SIZE][SIZE] = { 0 };
int perm_board[SIZE][SIZE] = { 0 };
int active_cell_x;
int active_cell_y;
int active_x;
int active_y;
char keypress;

void erase(int x, int y, int w, int h);
void homeScreen();
void drawBoard();
void findActiveCell();
void exitScreen();
void game();
void highlightCell();
void moveUP();
void moveDown();
void moveLeft();
void moveRight();
void clearCell(int x, int y);

void randomize(int n);
int randomNum();
int randomCheck(int row, int col, int value);
int isPresent(int element, int present[SIZE], int presentLastIndex);
int lineCheck(int row[SIZE]);
int checker(int answer[SIZE][SIZE]);

int main() {
    set_graphics(VGA_320X200X256);
    // do
    // {
        erase(1,1,400,220);
        homeScreen();
        keypress = (char)getch();
    
        if (keypress == EASY_ROUND) {
            randomize(EASY);
        }
        else if (keypress == MEDIUM_ROUND) {
            randomize(MEDIUM);
        }
        else if (keypress == HARD_ROUND) {
            randomize(HARD);
        }
        else if (keypress == QUIT) {
            exitScreen();
        }
        game();
        
    //} while (keypress != QUIT);
    return 0;
}

void game() {
    drawBoard();
    findActiveCell();
    do {
        keypress = (char)getch();
        
        switch(keypress) {
            case BACK:
                erase(1,1,400,220);
                homeScreen();
                break;
            case UP:
                moveUP();
                break;
            case DOWN:
                moveDown();
                break;
            case LEFT:
                moveLeft();
                break;
            case RIGHT:
                moveRight();
                break;
            case ONE:
                break;
            case TWO:
                break;
            case THREE:
                break;
            case FOUR:
                break;
            case FIVE:
                break;
            case SIX:
                break;
            case SEVEN:
                break;
            case EIGHT:
                break;
            case NINE:
                break;
        }
    }while (keypress != SUBMIT || keypress != QUIT);
    exitScreen();
}

void exitScreen() {
    set_graphics(VGA_TEXT80X25X16);
    clrscr();
}

void erase(int x, int y, int w, int h){
    int i,j;
    for (i = y; i <= (y + h); i++){
        for (j = x; j <= (x + w); j++){
            write_pixel(j,i,WHITE);
        }
    }
}

void clearCell(int x, int y){
    int i,j;
    for (i = y; i <= x+20; i++){
        for (j = x; j <= y+20; j++){
            write_pixel(j,i,WHITE);
        }
    }
}

void drawBoard(){
    int i, j, x_coor, y_coor;
    char temp;
    x_coor = 100;
    y_coor = 10;
    
    erase(1,1,400,220);
    write_text("0-9", 5, 10, BLACK, 0);
    write_text("W:UP", 5, 30, BLACK, 0);
    write_text("A:LEFT", 5, 50, BLACK, 0);
    write_text("S:DOWN", 5, 70, BLACK, 0);
    write_text("D:RIGHT", 5, 90, BLACK, 0);
    write_text("G:SUBMIT", 5, 110, BLACK, 0);
    write_text("B:BACK", 5, 130, BLACK, 0);
    write_text("X:QUIT", 5, 150, BLACK, 0);
    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                write_text("_|", x_coor, y_coor, BLACK, 1);
            }
            else {
                switch(board[i][j]) {
                    case 1:
                        write_text("1|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 2:
                        write_text("2|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 3:
                        write_text("3|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 4:
                        write_text("4|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 5:
                        write_text("5|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 6:
                        write_text("6|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 7:
                        write_text("7|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 8:
                        write_text("8|", x_coor, y_coor, BLACK, 1);
                        break;
                    case 9:
                        write_text("9|", x_coor, y_coor, BLACK, 1);
                        break;
                    default:
                        break;
                }
            }
            x_coor += 20;
        }
        x_coor = 100;
        y_coor += 20;
    }
    
}

void findActiveCell() {
    int i, j;
    int flag = 0;
    active_x = 100;
    active_y = 10;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (perm_board[i][j] == 0) {
                active_cell_x = i;
                active_cell_y = j;
                active_x = 100 + (i * 20);
                active_y = 10 + (j * 20);
                flag = 1;
                break;
            }
            }
        if (flag == 1) {
            break;
        }
    }
    highlightCell();
}

void moveUP() {
    if ((active_cell_x - 1) >= 0) {
        clearCell(active_x,active_y);
        write_text(" ", active_x, active_y, WHITE, 0);
        while (perm_board[active_cell_x-1][active_cell_y] == 1) {
            active_cell_x -= 1;
            active_y -= 20;
        }
        active_cell_x -= 1;
        active_y -= 20;
        highlightCell();
    }
}

void moveDown() {
    if ((active_cell_x + 1) < 9) {
        clearCell(active_x,active_y);
        write_text(" ", active_x, active_y, WHITE, 0);
        while (perm_board[active_cell_x+1][active_cell_y] == 1) {
            active_cell_x += 1;
            active_y += 20;
        }
        active_cell_x += 1;
        active_y += 20;
        highlightCell();
    }
}

void moveRight() {
    if ((active_cell_y + 1) < 9) {
        clearCell(active_x,active_y);
        write_text(" ", active_x, active_y, WHITE, 0);
        while (perm_board[active_cell_x][active_cell_y+1] == 1) {
            active_cell_y += 1;
            active_x += 20;
        }
        active_cell_y += 1;
        active_x += 20;
        highlightCell();
    }
}

void moveLeft() {
    if ((active_cell_y - 1) >= 0) {
        clearCell(active_x,active_y);
        write_text(" ", active_x, active_y, WHITE, 0);
        while (perm_board[active_cell_x][active_cell_y-1] == 1) {
            active_cell_y -= 1;
            active_x -= 20;
        }
        active_cell_y -= 1;
        active_x -= 20;
        highlightCell();
    }
}

void highlightCell() {
    write_text("X", active_x, active_y, RED, 0);
}


void homeScreen() {
    write_text("SUDOKU",130, 40, BLACK, 1);
    write_text("E - Easy", 120, 70, BLACK, 0);
    write_text("M - Medium", 120, 90, BLACK, 0);
    write_text("H - Hard", 120, 110, BLACK, 0);
    write_text("X - Quit", 120, 130, BLACK, 0);
}

int randomNum() {
    int n;
    
    n = rand() % 9 + 1;
    
    return n;
}

int randomCheck(int row, int col, int value) {
    int i = 0;
    
    //horizontal check
    for (i = 0; i < SIZE; i++) {
        if (board[row][i] == value) {
            return -1;
        }
    }
    
    //vertical check
    for (i = 0; i < SIZE; i++) {
        if(board[i][col] == value) {
            return -1;
        }
    }
    
    return 1;
}

void randomize(int n) {
	int row, col, value;

	while (n > 0) {
		value = randomNum();
		printf("%d\n", value);
		do {
			row = randomNum() - 1;
 	        col = randomNum() - 1;
		} while (board[row][col] != 0);
		
		do {
		    value = randomNum();
		}while (randomCheck(row, col, value) == -1);
		
		board[row][col] = value;
		perm_board[row][col] = 1;
	  	n--;
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