#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * alphabet = "abcdefghijklmnopqrstuvwxyz";
const int L_CHAR_OFFSET = 97;
char decipherLetter(int cypText, int keyText);
char encryptLetter(char * plain);
int processSignature(char * signature, char * key, char mode);

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
    //TODO merge behaviour using dynamic argument locations
    //first step: put methods into own functions like initBoard?
    mark.x = 0;
    mark.y = 0;

    //init board
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            board[j][i] = argv[1][i*6 + j];
            //printf("%c", board[j][i]);
        }
        //printf("\n");
    }
    //printf("\n");

    char key[strlen(argv[1])];
    char signature[strlen(argv[2])];

    strcpy(key, argv[1]);
    strcpy(signature, argv[2]);

    if(*argv[2] == '%'){ 
        processSignature(signature, key, 'e');
        printf("Encrypted: %s\n", signature+1);
    } else {
        processSignature(signature, key, 'd');
        printf("Decrypted: %s\n", signature+1);
    }

}

/* return: 1 if worked, 0 elsewise 
 * 
 */
int processSignature(char * signature, char * key, char mode){
    //l    loop thru message
    int i;
    if(strlen(signature) == 0 || strlen(key) == 0)
        return 0;
    i = (mode == 'e'?1:0);

    while(i < strlen(signature)){
        if(mode == 'e'){
            signature[i] = encryptLetter(&signature[i]);
        } else {
            //signature[i] = decipherLetter(&signature[i]);
        }
        i++;
    }
    return 1;
}

char encryptLetter(char * plain){
    int plainX;
    int plainY; 
    setCharLocation(&plainX, &plainY, plain);
    int markVal = getCharValue(&board[mark.x][mark.y]);

    int markIncX = markVal%6;
    int markIncY = markVal/6;

    int cipherX = (plainX + markIncX)%6;
    int cipherY = (plainY + markIncY)%6;

    char enc = board[cipherX][cipherY];

    int ciphVal = getCharValue(&enc);
    int ciphIncX = ciphVal%6;
    int ciphIncY = ciphVal/6;

    //shift row according to algorithm, Y for row start, X for col start

    shiftRow(&plainY);
    //prevent row shift from misaligning stored cipher location
    if(cipherY == plainY){
        cipherX++;
    }
    shiftCol(&cipherX);

    //wrap around marker
    mark.x = (mark.x + ciphIncX)%6;
    mark.y = (mark.y + ciphIncY)%6;

    //    printState(plain, &enc);
    return enc;
}

char decipherLetter(int cypText, int keyText){
    int cyp = cypText-L_CHAR_OFFSET;
    int key = keyText-L_CHAR_OFFSET;
    int r = (cyp - key) % 26;  
    //handle C's remainder behaviour
    return (r < 0) ? 26 - abs(r): r; 
}

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
