#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char * paperfold(int i, char * str);

int main(int argc, char * argv[]){
    if(argc < 2){
        printf("Please provide an argument in the form ./a.out #iter\n");
        return -1;
    }
    int exp = 0;
    sscanf(argv[1], "%d", &exp); 

    char str[(int)(pow(2,exp))];
    str[0] = '\0';

    paperfold(exp, str);
}

char * paperfold(int i, char * str) {
    if(i == 0)
        return str;
    //add 1 to end TODO shorten
    char one[2];
    one[0] = '1';
    one[1] = '\0';
    strcat(str, one);

    //add inverse to end of str
    int end = strlen(str)-2;
    while(end >= 0){
        //TODO alternative to appendVal
        char appendVal[2];
        (str[end] == '0' ? (appendVal[0] = '1') : (appendVal[0] = '0'));
        appendVal[1] = '\0';
        strcat(str, appendVal);
        end--;
    }
    printf("|--|%s\n", str);

    //recurse
    paperfold(i-1, str);
}
