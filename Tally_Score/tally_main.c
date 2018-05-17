#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

const int CHAR_START_U = 'A';
const int CHAR_START_L = 'a';

typedef struct {
    char id;
    int score;
} player;

int cmpFunc(const void * a, const void * b){
    int l = ((player *)a)->score;
    int r = ((player *)b)->score;
    return (r-l);
}

int main(int argc, char * argv[]){
    if(argc < 2){
        printf("Please provide a score to count.\n");
        return -1;
    }

    char * inputStr = argv[1];
    player players[5]; 

    //populate players with ids ranging from a to e
    for(int i = 0; i < 5; i++){
        players[i].id = 'a'+i;
        players[i].score = 0;
    }

    //use the alphabet and offset to access array indices
    for(int i = 0; i < strlen(inputStr); i++){
        if(isupper(inputStr[i])){
            players[inputStr[i] - CHAR_START_U].score--;
        } else {
            players[inputStr[i]- CHAR_START_L].score++;
        }
    }
    qsort(players, 5, sizeof(player), cmpFunc); 

    for(int i = 0; i < 5; i++){
        printf("| %c:%d ", players[i].id, players[i].score);
    }
    printf("\n");
}
