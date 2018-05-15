#include <stdio.h>
#include <math.h>

char getDigitStateAtIndex(int gridNum, int digitIndex, char board[][28]);

int main(){
    FILE *fp;
    char digitBoard[3][28];

    fp = fopen("./input.txt", "r");
    fgets(digitBoard[0], 255, (FILE*)fp);
    digitBoard[0][27] = '\0';
    fgets(digitBoard[1], 255, (FILE*)fp);
    digitBoard[1][27] = '\0';
    fgets(digitBoard[2], 255, (FILE*)fp);
    digitBoard[2][27] = '\0';
    

    //getDigitStateAtIndex(1, 5, digitBoard);
    //printf("\n");

    /*    printf("%s\n", digitBoard[0]);
          printf("%s\n", digitBoard[1]);
          printf("%s\n", digitBoard[2]);*/

    //printf("Test digit state: %c\n", getDigitStateAtIndex(4, 4, digitBoard)); 
    int nums[10];

    for(int i = 0; i<9; i++){
        if(getDigitStateAtIndex(i, 1, digitBoard) == ' '){
            if(getDigitStateAtIndex(i, 3, digitBoard) == ' '){
                nums[i] = 1;
            } else {
                nums[i] = 4;
            }
        } else {
            if(getDigitStateAtIndex(i, 3, digitBoard) == ' '){
                //2, 3, 7
                if(getDigitStateAtIndex(i, 4, digitBoard) == ' '){
                    nums[i] = 7;
                } else {
                    if(getDigitStateAtIndex(i, 6, digitBoard) == ' ')
                        nums[i] = 3;
                    else
                        nums[i] = 2;
                }
            } else {
                if(getDigitStateAtIndex(i, 5, digitBoard) == ' '){
                    //5, 6
                    if(getDigitStateAtIndex(i, 6, digitBoard) == ' ')
                        nums[i] = 5;
                    else
                        nums[i] = 6;
                } else {
                    //8, 9
                    if(getDigitStateAtIndex(i, 6, digitBoard) == ' ')
                        nums[i] = 9;
                    else
                        nums[i] = 8;
                }
            }
        }
    }
    for(int i = 0; i <9; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");
}


char getDigitStateAtIndex(int gridNum, int digitIndex, char board[][28]){
    int x = (gridNum*3) + (digitIndex%3);
    //printf("The row number: %d\n", x); 
    int y = floor(digitIndex/3);
    //printf("The col number: %d\n", y); 
    //printf("%c", board[y][x]);
    return board[y][x];
}
