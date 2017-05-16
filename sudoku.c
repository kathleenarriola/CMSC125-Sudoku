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

#define ONE '1'
#define TWO '2'
#define THREE '3'
#define FOUR '4'
#define FIVE '5'
#define SIX '6'
#define SEVEN '7'
#define EIGHT '8'
#define NINE '9'

#define TL -1
#define TM -2
#define TR -3
#define ML -4
#define MM -5
#define MR -6
#define LR -7
#define LM -8
#define LL -9

/* global variables */
int board[SIZE][SIZE] = { 0 };
int perm_board[SIZE][SIZE] = { 0 };
int active_cell_x;
int active_cell_y;
int active_x;
int active_y;
int isWinner;
int boxIndex;
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
void writeNumber(char num);

void randomize(int n);
int randomNum();
int randomCheck(int row, int col, int value);
int isPresent(int element, int present[SIZE], int presentLastIndex);
int lineCheck(int row[SIZE]);
int checker(int answer[SIZE][SIZE]);

int main() {
    set_graphics(VGA_320X200X256);
    do {
        srand(time());
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
        game();
        
    } while (keypress != QUIT);
    
    exitScreen();

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
                main();
                //homeScreen();
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
                writeNumber(ONE);
                break;
            case TWO:
                writeNumber(TWO);
                break;
            case THREE:
                writeNumber(THREE);
                break;
            case FOUR:
                writeNumber(FOUR);
                break;
            case FIVE:
                writeNumber(FIVE);
                break;
            case SIX:
                writeNumber(SIX);
                break;
            case SEVEN:
                writeNumber(SEVEN);
                break;
            case EIGHT:
                writeNumber(EIGHT);
                break;
            case NINE:
                writeNumber(NINE);
                break;
            case SUBMIT:
            	if (checker(board) == 1) {
		            erase(1,1, 400, 220);
		            write_text("Winner", 120, 50, BLACK, 1);
		        } else {
		            erase(1,1, 400, 220);
		            write_text("You Lose", 120, 50, BLACK, 1);
		        }
		        break;
		    case QUIT:
		    	exitScreen();
        }
    }while (keypress != SUBMIT || keypress != QUIT);
    
    exitScreen();

    if (keypress == SUBMIT) {
        if (checker(board) == 1) {
            erase(1,1, 400, 220);
            write_text("Winner", 120, 50, BLACK, 1);
        } else {
            erase(1,1, 400, 220);
            write_text("You Lose", 120, 50, BLACK, 1);
        }
    } else if (keypress == QUIT) {
        exitScreen();
    }
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
    int i, j;
    for (i = x; i < 20; i++) {
        for (j = y; j < 20; j++) {
             write_pixel(i,j,WHITE);
        }
    }
    write_text("-", active_x, active_y, WHITE, 0);
}

void drawBoard(){
    int i, j, x_coor, y_coor;
    char temp;
    x_coor = 100;
    y_coor = 10;
    
    erase(1,1,400,220);
    write_text("1-9", 5, 10, BLACK, 0);
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
            if (board[i][j] == 0) {
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
    if ((active_cell_x - 1) >= 0 && (active_y - 20) >- 20) {
        clearCell(active_x,active_y);
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
    if ((active_cell_x + 1) < 9 && (active_y + 20) < 200) {
        clearCell(active_x,active_y);
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
    if ((active_cell_y + 1) < 9 && (active_x + 20) < 400) {
        clearCell(active_x,active_y);
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
    if ((active_cell_y - 1) >= 0 && (active_x - 20) >= 100) {
        clearCell(active_x,active_y);
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

void writeNumber(char num) {
	switch(num) {
		case ONE:
			clearCell(active_x,active_y);
            write_text("1|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case TWO:
        	clearCell(active_x,active_y);
            write_text("2|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case THREE:
        	clearCell(active_x,active_y);
            write_text("3|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case FOUR:
        	clearCell(active_x,active_y);
            write_text("4|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case FIVE:
        	clearCell(active_x,active_y);
            write_text("5|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case SIX:
        	clearCell(active_x,active_y);
            write_text("6|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case SEVEN:
        	clearCell(active_x,active_y);
            write_text("7|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case EIGHT:
        	clearCell(active_x,active_y);
            write_text("8|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        case NINE:
        	clearCell(active_x,active_y);
            write_text("9|", active_x, active_y, RED, 1);
            findActiveCell();
            break;
        default:
            break;
	}
}

void homeScreen() {
    write_text("SUDOKU", 130, 40, BLACK, 1);
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

void checkBox(int x, int y) {
    int i, j;
    int TL[SIZE][2] = {
        {0,0}, {0,3}, {0,6}, {3,0}, {3,3}, {3,6}, {6,0}, {6,3}, {6,6}
    };
    int TM[SIZE][2] = {
        {0,1}, {0,4}, {0,7}, {3,1}, {3,4}, {3,7}, {6,1}, {6,4}, {6,7}
    };
    int TR[SIZE][2] = {
        {0,2}, {0,5}, {0,8}, {3,2}, {3,5}, {3,8}, {6,2}, {6,5}, {6,8}
    };
    int ML[SIZE][2] = {
        {1,0}, {1,3}, {1,6}, {4,0}, {4,3}, {4,6}, {7,0}, {7,3}, {7,6}
    };
    int MM[SIZE][2] = {
        {1,1}, {1,4}, {1,7}, {4,1}, {4,4}, {4,7}, {7,1}, {7,4}, {7,7}
    };
    int MR[SIZE][2] = {
        {1,2}, {1,5}, {1,8}, {4,2}, {4,5}, {4,8}, {7,2}, {7,5}, {7,8}
    };
    int LL[SIZE][2] = {
        {2,0}, {2,3}, {2,6}, {5,0}, {5,3}, {5,6}, {8,0}, {8,3}, {8,6}
    };
    int LM[SIZE][2] = {
        {2,1}, {2,4}, {2,7}, {5,1}, {5,4}, {5,7}, {8,1}, {8,4}, {8,7}
    };
    int LR[SIZE][2] = {
        {2,2}, {2,5}, {2,8}, {5,2}, {5,5}, {5,8}, {8,2}, {8,3}, {8,8}
    };

        
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