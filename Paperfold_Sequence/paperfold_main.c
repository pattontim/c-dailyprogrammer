#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * paperfold(int i, char * str);

int main(){
    char str[50];
    str[0] = '\0';
    paperfold(4, str);
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
    while(end-- >= 0){
        //TODO alternative to appendVal
        char appendVal[2];
        (str[end] == '0' ? (appendVal[0] = '1') : (appendVal[0] = '0'));
        appendVal[1] = '\0';
        strcat(str, appendVal);
    }
    printf("%s\n", str);

    //recurse
    paperfold(i-1, str);
}
