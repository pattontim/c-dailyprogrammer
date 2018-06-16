#include <stdio.h>

char intIsBaumSequence(unsigned int input);
//int firstBitSet(unsigned int input);
char isEven(int input);

int main(){
    int baum_n = 0;
    scanf("%d", &baum_n);

    for(unsigned int i = 0; i <= baum_n; i++){
        printf("%d, ", intIsBaumSequence(i));
    } 
    printf("x|\n");
}

/*//return 1 if true, 0 if false
int firstBitSet(unsigned int input){
    //return true if and it against 1 and get 1
    return input & 1;
}*/

char isEven(int input){
    return !(input & 1);
}

char intIsBaumSequence(unsigned int input){
    int count = 0;
    while(input != 0){
        //checks if a zero is present in first bit
        if(isEven(input))
            count++;
        else
            //reached a 1
            if (!isEven(count))
                return 0;
        input = input >> 1;
    }
    return 1;
}
