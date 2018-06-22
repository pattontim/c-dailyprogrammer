#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int processSignature(char * signature, char * key, char mode);
char processLetter(char * pl, char mode);

void setCharLocation(int * x, int * y, char * plain);
int getCharValue(char * c);

void shiftRow(int * row);
void shiftCol(int * col);

void printState(char * pt, char * ct);
void printVectors();

char board[6][6];

struct marker {
    int x;
    int y;
} mark;


int main(int argc, char * argv[]){
    if(argc < 3){
        printf("%s", "Proper program use: ./a.out key \%plain\n ./a.out key encrypted\n");
        return 0;
    }

    mark.x = 0;
    mark.y = 0;

    //init board
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            board[j][i] = argv[1][i*6 + j];
        }
    }

    char key[strlen(argv[1])];
    char signature[strlen(argv[2])];

    strcpy(key, argv[1]);
    strcpy(signature, argv[2]);

    if(*argv[2] == '%'){ 
        processSignature(signature, key, 'e');
        printf("Encrypted: %s\n", signature+1);
    } else {
        processSignature(signature, key, 'd');
        printf("Decrypted: %s\n", signature);
    }

}

/* return: 1 if worked, 0 elsewise 
 * 
 */
int processSignature(char * signature, char * key, char mode){
    int i;
    if(strlen(signature) == 0 || strlen(key) == 0)
        return 0;
    //offset command flag
    i = (mode == 'e'?1:0);

    while(i < strlen(signature)){
        signature[i] = processLetter(&signature[i], mode);
        i++;
    }
    return 1;
}

char processLetter(char * pl, char mode){
    int plainX, plainY, cipherX, cipherY;
    char ret;

    int markVal = getCharValue(&board[mark.x][mark.y]);
    int markIncX = markVal%6;
    int markIncY = markVal/6;

    //use plain to get enc
    if(mode == 'e'){
        setCharLocation(&plainX, &plainY, pl);
        cipherX = (plainX + markIncX)%6;
        cipherY = (plainY + markIncY)%6;
        ret = board[cipherX][cipherY];
    //use enc to get plain 
    } else {
        setCharLocation(&cipherX, &cipherY, pl);
        plainX = (cipherX + (-markIncX))%6;
        plainY = (cipherY + (-markIncY))%6;
        //handle C's negative remainder behaviour
        plainX = (plainX < 0) ? 6 - abs(plainX): plainX;  
        plainY = (plainY < 0) ? 6 - abs(plainY): plainY;  
        ret = board[plainX][plainY];
    }

    int ciphVal = getCharValue(&board[cipherX][cipherY]);
    int ciphIncX = ciphVal%6;
    int ciphIncY = ciphVal/6;

    //according to algorithm, Y for row start, X for col start
    shiftRow(&plainY);
    //prevent row shift from misaligning stored cipher location
    if(cipherY == plainY){
        cipherX = (cipherX+1)%6;
    }
    shiftCol(&cipherX);

    //wrap around marker
    mark.x = (mark.x + ciphIncX)%6;
    mark.y = (mark.y + ciphIncY)%6;

    return ret;
}

//based on LC4 alphabet and C offsets
int getCharValue(char * c){
    if(*c <= '9' && *c >= '2')
        return *c - '2' + 2;
    else if(*c <= 'z' && *c >= 'a')
        return *c - 'a' + 10;
    else if(*c == '#')
        return 0;
    else
        return 1;
}

void setCharLocation(int * x, int * y, char * plain){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(board[i][j] == *plain){
                *x = i;
                *y = j;
            }
        }
    }
}

void shiftRow(int * row){
    if(mark.y == *row)
        mark.x = (mark.x+1)%6;

    char move = board[5][*row];
    for(int i = 5; i > 0; i--){
        board[i][*row] = board[i-1][*row];
    }
    board[0][*row] = move;
}

void shiftCol(int * col){
    if(mark.x == *col)
        mark.y = (mark.y+1)%6;

    char move = board[*col][5];
    for(int i = 5; i > 0; i--){
        board[*col][i] = board[*col][i-1];
    }
    board[*col][0] = move;
}

void printState(char * pt, char * ct){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            printf("%c", board[j][i]);
        }
        printf("\n");
    }
    printf("m: (%d,%d)", mark.x, mark.y);
    printf("pt: %c ", *pt);
    printf("ct: %c\n", *ct);
}

void printVectors(){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            int plainVal = getCharValue(&board[i][j]);
            printf("pt: %c, xVec: %d, yVec: %d\n", board[i][j], plainVal%6, plainVal/6);
        }
        //printf("\n");
    }

}
