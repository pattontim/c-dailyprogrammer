#include <stdio.h>
#include <math.h>

char getDigitStateAtIndex(int gridNum, int digitIndex, char board[][28]);
int getDigitAtGrid(int gridNum, char digitBoard[][28]);

static int display_map[] = {0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b};

int main(){
    FILE *fp;
    char digitBoard[3][28];

    fp = fopen("./input.txt", "r");

    if(fp == NULL){
        exit("Input file not found./n");
    }

    // check if file successfully opened
    for(int i = 0; i < 3; i++){
        fgets(digitBoard[i], 255, (FILE*)fp);
        digitBoard[i][27] = '\0';
    }

    //print 
    for(int i = 0; i <9; i++){
        printf("%d ", getDigitAtGrid(i, digitBoard));
    }
    printf("\n");
}

// gridNum is the location eg zero is [1]23456789
int getDigitAtGrid(int gridNum, char digitBoard[][28]){
    int xOffset = gridNum * 3;
    int result = 0;
    result |= (digitBoard[0][xOffset + 1] == '_')<<6;
    result |= (digitBoard[1][xOffset + 2] == '|')<<5;
    result |= (digitBoard[2][xOffset + 2] == '|')<<4;
    result |= (digitBoard[2][xOffset + 1] == '_')<<3;
    result |= (digitBoard[2][xOffset + 0] == '|')<<2;
    result |= (digitBoard[1][xOffset + 0] == '|')<<1;
    result |= (digitBoard[1][xOffset + 1] == '_')<<0;
    for(int i = 0; i < 10; i++){
        if(display_map[i] == result){
            return i;
        }
    }
    return -1;
    // same model as digit search
}

//grids are 3x3 squares, of which there are 9 in a board
// int getDigitAtGrid(int gridNum, char digitBoard[][28]){ 
//         if(getDigitStateAtIndex(gridNum, 1, digitBoard) == ' '){
//             if(getDigitStateAtIndex(gridNum, 3, digitBoard) == ' '){
//                 return 1;
//             } else {
//                 return 4;
//             }
//         } else {
//             if(getDigitStateAtIndex(gridNum, 3, digitBoard) == ' '){
//                 if(getDigitStateAtIndex(gridNum, 4, digitBoard) == ' '){
//                     return 7;
//                 } else {
//                     if(getDigitStateAtIndex(gridNum, 6, digitBoard) == ' ')
//                         return 3;
//                     else
//                         return 2;
//                 }
//             } else {
//                 if(getDigitStateAtIndex(gridNum, 5, digitBoard) == ' '){
//                     if(getDigitStateAtIndex(gridNum, 6, digitBoard) == ' ')
//                         return 5;
//                     else
//                         return 6;
//                 } else {
//                     if(getDigitStateAtIndex(gridNum, 6, digitBoard) == ' ')
//                         return 9;
//                     else
//                         return 8;
//                 }
//             }
//         }
//     }

char getDigitStateAtIndex(int gridNum, int digitIndex, char board[][28]){
    int x = (gridNum*3) + (digitIndex%3);
    int y = floor(digitIndex/3);
    return board[y][x];
}
