//TODO perform algorithm analysis on this
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int containsPattern(char * compared, char * pattern);
char intArrayContainsInt(int * arr, int aInt, int numElems);
void strcat_c (char *str, char c);
long factorial(int n);

int main(){
    char input[100];
    printf("Please enter the input: ");
    scanf("%s", input); 

    int length = strlen(input);
    int arrCount = 0;
    char patFound = 0;
    char temp[length/2];

    //formula for max patterns
    int outputVal[2*length];

    for(int i = 0; i < length; i++){
        strcpy(temp, "");
        strcat_c(temp, input[i]);
        //length of a pattern will never be longer than half of the array
        for(int j = i+1; (j-i < length/2) && j < length; j++){
            char aChar = input[j];
			strcat_c(temp, aChar);
            //checking paradigm can be reversed to store possible patterns
            int patCount = containsPattern(input, temp);
            if(patCount > 1){
                 if(!intArrayContainsInt(outputVal, atoi(temp), arrCount)){
                    patFound = 1;
                    outputVal[arrCount++] = atoi(temp);
                    printf("%s:%d ", temp, patCount); 
                }
		    }
        }
    }
    if(!patFound)
        printf("0\n"); 
    printf("\n");
}

//returns the number of times the pattern is contained in the given string
int containsPattern(char * compared, char * aPattern){ 
    int count = 0;
    int patLen = strlen(aPattern);
    int patCount = 0;
    for(int i = 0; i < strlen(compared); i++){
        if(compared[i] == aPattern[0]){
            count = 0;
            //check number against pattern
            for(int j = 0; j < patLen; j++){
                if(aPattern[j] == compared[i+j]){
                    count++;
                } 
            }
            //TODO avoid rechecking numbers
            if(count >= strlen(aPattern)){
                patCount++;
            }
        }
    }
    return patCount;
}

char intArrayContainsInt(int * arr, int aInt, int numElems){
    for(int i = 0; i < numElems; i++){
        if(arr[i] == aInt)
            return 1;
    }
    return 0;
}

void strcat_c (char *str, char c)
  {
    for (;*str;str++); // note the terminating semicolon here. 
    *str++ = c; 
    *str++ = 0;
  }
