#include <stdio.h>
#include <math.h>

char getDigitStateAtIndex(int gridNum, int digitIndex, char board[][28]);
int getDigitAtGrid(int gridNum, char digitBoard[][28]);

int main(){
    FILE *fp;
    char digitBoard[3][28];

    //read in input board
    fp = fopen("./input.txt", "r");
    fgets(digitBoard[0], 255, (FILE*)fp);
    digitBoard[0][27] = '\0';
    fgets(digitBoard[1], 255, (FILE*)fp);
    digitBoard[1][27] = '\0';
    fgets(digitBoard[2], 255, (FILE*)fp);
    digitBoard[2][27] = '\0';

    //print 
    for(int i = 0; i <9; i++){
        printf("%d ", getDigitAtGrid(i, digitBoard));
    }
    printf("\n");
}

//grids are 3x3 squares, of which there are 9 in a board
int getDigitAtGrid(int gridNum, char digitBoard[][28]){ 
        if(getDigitStateAtIndex(gridNum, 1, digitBoard) == ' '){
            if(getDigitStateAtIndex(gridNum, 3, digitBoard) == ' '){
                return 1;
            } else {
                return 4;
            }
        } else {
            if(getDigitStateAtIndex(gridNum, 3, digitBoard) == ' '){
                if(getDigitStateAtIndex(gridNum, 4, digitBoard) == ' '){
                    return 7;
                } else {
                    if(getDigitStateAtIndex(gridNum, 6, digitBoard) == ' ')
                        return 3;
                    else
                        return 2;
                }
            } else {
                if(getDigitStateAtIndex(gridNum, 5, digitBoard) == ' '){
                    if(getDigitStateAtIndex(gridNum, 6, digitBoard) == ' ')
                        return 5;
                    else
                        return 6;
                } else {
                    if(getDigitStateAtIndex(gridNum, 6, digitBoard) == ' ')
                        return 9;
                    else
                        return 8;
                }
            }
        }
    }

char getDigitStateAtIndex(int gridNum, int digitIndex, char board[][28]){
    int x = (gridNum*3) + (digitIndex%3);
    int y = floor(digitIndex/3);
    return board[y][x];
}
