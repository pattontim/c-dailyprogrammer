#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int processSequence(char * key, char * sequence, char * signature, char * header, char mode);
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
            board[j][i] = argv[2][i*6 + j];
        }
    }

    char argument = *argv[1];

    if(argc >= 4){
        char key[strlen(argv[2])+1];
        char sequence[strlen(argv[3])+1];
        char signature[11];
        char header[17];
        
        //why is this undefined behaviour?
        //key[0] = sequence[0] = signature[0] = header[0] = '\0';
        strcpy(key, argv[2]);
        strcpy(sequence, argv[3]);
        strcpy(signature, "");
        strcpy(header, "");
        if(argc >= 5 && argc <= 6){
            if(argument == 's' && strlen(argv[4]) == 10){
                strcpy(signature, argv[4]);
                strcpy(header, argv[5]);
            } else if(argument == 'u' && strlen(argv[4]) == 16) {
                strcpy(header, argv[4]);
            } else {
                //erroneous input
                return -1;
            }
        }
        //printf("key: %s\n", key);
        //printf("sequence: %s\n", sequence);
        //printf("signature: %s\n", signature);
        //printf("header: %s\n", header);
        processSequence(key, sequence, signature, header, argument);
        printf("Result: %s\n", sequence);
        }
}

/* return: 1 if worked, 0 elsewise 
 * 
 */
int processSequence(char * key, char * sequence, char * signature, char * header, char mode){
    int i = 0;
    switch(mode){
        case 'e':
        case 'd':
            while(i < strlen(sequence)){
                char val = processLetter(&sequence[i], mode); 
                sequence[i] = val;
                i++;
            }       
            break;
        case 's':
        case 'u':
            //set state after nonce generation
            //restart with e and d as necessary and set signature?
            break;
        default:
            //lolol
            break;
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
