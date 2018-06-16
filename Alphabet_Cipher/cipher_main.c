#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * alphabet = "abcdefghijklmnopqrstuvwxyz";
const int L_CHAR_OFFSET = 97;
char decipherLetter(int cypText, int keyText);
char encryptLetter(int plainText, int keyText);
int encryptMessage(char * plain, char * secret);
int decryptMessage(char * encrypted, char * secret);

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
    char plainText[strlen(argv[2])];
    char secretCode[strlen(argv[1])];
    strcpy(plainText, argv[2]);
    strcpy(secretCode, argv[1]);
    char decipheredStr[strlen(plainText)];
    encryptMessage(plainText, secretCode);
    printf("%s\n", plainText);
}


/* return: 1 if worked, 0 elsewise 
 * 
 */
int encryptMessage(char * plain, char * secret){
    //loop thru message
    int i = 0;
    if(strlen(plain) == 0 || strlen(secret) == 0)
        return 0;

    while(i < strlen(plain)){
        int index = encryptLetter(plain[i], secret[i%strlen(secret)]);
        plain[i] = alphabet[index];
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

char encryptLetter(int plainText, int keyText){
    int plain = plainText-L_CHAR_OFFSET;
    int key = keyText-L_CHAR_OFFSET;
    return (plain + key)%26;
}

char decipherLetter(int cypText, int keyText){
    int cyp = cypText-L_CHAR_OFFSET;
    int key = keyText-L_CHAR_OFFSET;
    int r = (cyp - key) % 26;  
    //handle C's remainder behaviour
    return (r < 0) ? 26 - abs(r): r; 
}
