#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char * dragonfold(int i, char * str);

int main(int argc, char * argv[]){
    if(argc < 2){
        printf("Please provide an argument in the form ./paperfold <num>\n");
        return -1;
    }

    //computes required size for maximum dragonfold sequence
    int exp = 0;
    sscanf(argv[1], "%d", &exp); 

    char str[(int)(pow(2,exp))];
    str[0] = '\0';

    dragonfold(exp, str);
}

/*
*   Input: Number of stages and an address to hold the result
*   Output: The Dragonfold sequence at the final stage
*/
char * dragonfold(int i, char * str) {
    if(i == 0)
        return str;
    
    // Apply algorithm by appending 1 to existing
    char one[2];
    one[0] = '1';
    one[1] = '\0';
    strcat(str, one);

    // Accounts for newly appended 1
    int end = strlen(str)-2;

    // Constructs second half by working backwards on the original
    while(end >= 0){
        char appendVal[2];
        (str[end] == '0' ? (appendVal[0] = '1') : (appendVal[0] = '0'));
        appendVal[1] = '\0';
        strcat(str, appendVal);
        end--;
    }
    printf("|---|%s\n", str);

    dragonfold(i-1, str);
}
