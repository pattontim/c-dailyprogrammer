#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * alphabet = "abcdefghijklmnopqrstuvwxyz";
const int L_CHAR_OFFSET = 97;
char decipherLetter(int cypText, int keyText);
char encryptLetter(char * plain);
int encryptMessage(char * plain, char * secret);
int decryptMessage(char * encrypted, char * secret);

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
    int i = 0;
    if(*argv[1] == 'd'){
        char encrypted[strlen(argv[3])];
        char secretCode[strlen(argv[2])];
        strcpy(encrypted, argv[3]);
        strcpy(secretCode, argv[2]);
        decryptMessage(encrypted, secretCode);
        printf("%s\n", encrypted);
        return -1;
    }

    //2nd argument is key, unencrypted is 3rd
    //init board
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            board[j][i] = argv[1][i*6 + j];
            //printf("%c", board[j][i]);
        }
        //printf("\n");
    }

    //printf("\n");

    //init marker
    mark.x = 0;
    mark.y = 0;

    char plainText[strlen(argv[2])];
    char secretCode[strlen(argv[1])];
    strcpy(plainText, argv[2]);
    strcpy(secretCode, argv[1]);
    encryptMessage(plainText, secretCode);
    printf("Encrypted: %s\n", plainText);
}

/* return: 1 if worked, 0 elsewise 
 * 
 */
int encryptMessage(char * plain, char * secret){
    //l    loop thru message
    int i = 0;
    if(strlen(plain) == 0 || strlen(secret) == 0)
        return 0;

    while(i < strlen(plain)){
        plain[i] = encryptLetter(&plain[i]);
        i++;
    }
    return 1;
}

/* return: 1 if worked, 0 elsewise 
 * 
 */
int decryptMessage(char * encrypted, char * secret){
    int i = 0;
    if(strlen(encrypted) == 0 || strlen(secret) == 0)
        return 0;

    while(i < strlen(encrypted)){
        int index = decipherLetter(encrypted[i], secret[i%strlen(secret)]);
        char letter = alphabet[index];
        encrypted[i] = letter;
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

    shiftRow(&plainY);

    //prevent row shift from misaligning stored cipher location
    if(cipherY == plainY){
        cipherX++;
    }

    shiftCol(&cipherX);

    //update cipherX & Y when chars are moved!

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
