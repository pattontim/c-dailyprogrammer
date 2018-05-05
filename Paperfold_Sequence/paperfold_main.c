#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* itoa(int, char* , int);

int main(){
    char str[50];
    strcpy(str, "10111");
    int end = strlen(str)-1;
    int j = end-1;
    while(j >= 0){
        int newVal = end-j;
        int currentChar = (str[j] == '0');
        char appendVal[1];
        //FIGURE OUT HOW TO APPEND CHAR OR USE IF STATEMENT
        //sprintf(appendVal, "%d", currentChar);
        //printf("Append val: %s\n", appendVal);
        //strcat(str, appendVal); 
        if(str[j] == 0){
            //
        }

        sprintf(str+strlen(str), (str[j] == '0'));

        printf("appending %d\n", currentChar);
        printf("at index %d\n", end+newVal);
        printf("new val: %d\n", newVal);
        printf("j: %d\n", j);
        j--;
    }
    printf("%s\n", str);
}

/*char * paperfold(int i, char * str) {
    if(i = 0)
        return str;
    //add 1 to end
    strcat(str, '1');

    //add reverse string to end
    int j = (strlen(str)-1)-1;
    while(j >= 0){
        printf("%d", j);
        j--;
    }

    //call recursive case.
}*/
