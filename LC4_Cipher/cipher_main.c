#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>


int processSequence(char * key, char * sequence, char * signature, char * header, char mode);
char processLetter(char * pl, char mode);

void setCharLocation(int * x, int * y, char * plain);
int getCharValue(char * c);

void shiftRow(int * row);
void shiftCol(int * col);

void printState(char * pt, char * ct);
void printVectors();

void setState(char * key, char * nonce, char * header);
char board[6][6];
void seed_rng(void);

struct marker {
	int x;
	int y;
} mark;

char * boardIndex ="#_23456789abcdefghijklmnopqrstuvwxyz"; 

const int NONCE_SIZE = 6, SIGNATURE_SIZE=10, HEADER_SIZE = 16;

int main(int argc, char * argv[]){
	if(argc < 3){
		printf("%s", "Proper program use: ./a.out key \%plain\n ./a.out key encrypted\n");
		return 0;
	}

	//setState(argv[2], "", "");

	char argument = *argv[1];

	if(argc >= 4){
		char key[strlen(argv[2])+1];
		char sequence[NONCE_SIZE+strlen(argv[3])+SIGNATURE_SIZE+1];
		char signature[SIGNATURE_SIZE+1];
		char header[HEADER_SIZE+1];

		//why is this undefined behaviour?
		//key[0] = sequence[0] = signature[0] = header[0] = '\0';
		strcpy(key, argv[2]);
		strcpy(sequence, argv[3]);
		strcpy(signature, "");
		strcpy(header, "");
		if(argc == 5){
			if(argument == 's' && strlen(argv[4]) == 10){
				strcpy(signature, argv[4]);
			} else if(argument == 'u' && strlen(argv[4]) == 16) {
				strcpy(header, argv[4]);
			} else {
				//erroneous input
				return -1;
			}
		} else if(argc == 6){
            if(strlen(argv[5]) == 16 && strlen(argv[4]) == 10){
                strcpy(signature, argv[4]);
                strcpy(header, argv[5]);
            } else {
                return -1;
            }
        }
		//printf("key: %s\n", key);
		//printf("sequence: %s\n", sequence);
		//printf("signature: %s\n", signature);
		//printf("header: %s\n", header);

		processSequence(key, sequence, signature, header, argument);
		printf("Result: %s%s\n", sequence, signature);
		//processSequence(key, sequence, signature, header, 'u');
		//printf("Result: %s%s\n", sequence, signature);
	}
}

/* return: 1 if worked, 0 elsewise 
 *
 */
int processSequence(char * key, char * sequence, char * signature, char * header, char mode){
	int i = 0;
    int j = 0;
	switch(mode){
		case 'e':
		case 'd': {
            if(strlen(signature) == 0){
			    setState(key, "", "");
            }
			while(i < strlen(sequence)){
				char val = processLetter(&sequence[i], mode); 
				sequence[i] = val;
				i++;
			}       
            i = 0;
            while(i < strlen(signature)){
                char val = processLetter(&signature[i], mode);
                signature[i] = val;
                i++;
            }
        } break;
		case 's': {

            seed_rng(); 
            //0 to 35
	        //char nonce[7];
            char * nonce = "abcdef";
            /*for(int i = 0; i < 6; i++){
                nonce[i] = boardIndex[rand() % 36];
            }*/
            //generate characters randomly based on 
            printf("pre set state\n");
            setState(key, nonce, header);
            printf("processed state...\n");
            processSequence(key, sequence, signature, header, 'e');
            printf("After processing signed\n");
            printf("key: %s\n", key);
		    printf("sequence: %s\n", sequence);
		    printf("signature: %s\n", signature);
		    printf("header: %s\n", header);

            char s_buf[strlen(sequence)];
            strcpy(s_buf, sequence); 
            
            j = 0;
            while(j < NONCE_SIZE){
                sequence[j] = nonce[j];
                j++;
            }
            while(j < NONCE_SIZE+strlen(s_buf)){
                sequence[j] = s_buf[j-NONCE_SIZE];
                j++;
            }
        } break;

		case 'u': {
            int sigOffset = strlen(sequence)-SIGNATURE_SIZE;

            char nonce[NONCE_SIZE];
            int i = 0;
            while(i < NONCE_SIZE){
                nonce[i] = sequence[i]; 
                i++;
            }
            printf("Nonce: %s\n", nonce);
            setState(key, nonce, header);
            char s_buf[sigOffset-NONCE_SIZE+1];
            while(i < sigOffset){
                s_buf[i-NONCE_SIZE] = sequence[i];
                i++;
            }
            while(i < strlen(sequence)){
                signature[i-sigOffset] = sequence[i];
               i++;
            }
            signature[i-sigOffset] = '\0';
            strcpy(sequence, s_buf);
		    printf("sequence before: %s\n", sequence);
		    printf("signature before: %s\n", signature);
		    printf("header before: %s\n", header);
            processSequence(key, sequence, signature, header, 'd');
            //sequence[strlen(sequence)] = ' ';
            sequence[strlen(sequence)+1] = '\0';
            sequence[strlen(sequence)] = ' ';
            printf("--- After processing signed text ---\n");
            printf("key: %s\n", key);
		    printf("sequence: %s\n", sequence);
		    printf("signature: %s\n", signature);
		    printf("header: %s\n", header);



            //seq in the end should be [unenc][unenc-sig], if I pass them both in it will go into the result but I have to clear the signature from the result
			//restart with e and d as necessary and set signature?
        } break;
		default:
            break;
		    //lolol
           // break;
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

void setState(char * key, char * nonce, char * header){
	mark.x = 0;
	mark.y = 0; 
	//init board
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			board[j][i] = key[i*6 + j];
		}
	}
    int n = strlen(nonce);
    for(int i = 0; i < n; i++){
        processLetter(&nonce[i], 'e');
    }
    int h = strlen(header);
    for(int i = 0; i < h; i++){
        //printf("processing header\n");
        processLetter(&header[i], 'e');
    }
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

// Seed the random number generator.
void seed_rng(void) {
    int fp = open("/dev/random", O_RDONLY);
    if (fp == -1) abort();
    unsigned seed;
    unsigned pos = 0;
    while (pos < sizeof(seed)) {
        int amt = read(fp, (char *) &seed + pos, sizeof(seed) - pos);
        if (amt <= 0) abort();
        pos += amt;
    }
    srand(seed);
    close(fp);
}
