#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int CHAR_START_U = 'A';
const int CHAR_START_L = 'a';

typedef struct {
    char id;
    int score;
} player;

int main(){
    char * inputStr = "abcde";


    player players[5]; 
    for(int i = 0; i < 5; i++){
        players[i].id = 'a'+i;
        players[i].score = 0;
    }
    for(int i = 0; i < strlen(inputStr); i++){
        if(isupper(inputStr[i])){
            players[inputStr[i] - CHAR_START_U].score--;
        } else {
            players[inputStr[i]- CHAR_START_L].score++;
        }
    }

    //qsort(players, 5, sizeof(player), cmpFunc); 

    for(int i = 0; i < 5; i++){
        printf("%c:%d\n", players[i].id, players[i].score);
    }
}
