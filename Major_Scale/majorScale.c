#include <stdio.h>
#include <string.h>
#define NOTE_NUM 12

int selfedgeToIndex(char * name);
int noteToIndex(char * name);
char * note(char * aNote, char * se);

//TODO store notes in an index, write functions for retrieval
char * notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
char * selfedges[] = {"Do", "Re", "Mi", "Fa", "So", "La", "Ti"};
int selfVals[] ={0, 2, 4, 5, 7, 9, 11};

int main(){
   printf("%s\n", note("C", "Do"));
   printf("%s\n", note("C", "Re"));
   printf("%s\n", note("C", "Mi"));
   printf("%s\n", note("D", "Mi"));
   printf("%s\n", note("A#", "Fa"));
}

int noteToIndex(char * name){
    for(int i = 0; i < 12; i++){
        if(strcmp(notes[i], name) == 0)
            return i;
    }
}

int selfedgeToIndex(char * name){
    for(int i = 0; i < 7; i++){
        if(strcmp(selfedges[i], name) == 0)
            return selfVals[i];
    }
}

char * note(char * aNote, char * se){ 
    return notes[(noteToIndex(aNote)+selfedgeToIndex(se))%NOTE_NUM];
}
