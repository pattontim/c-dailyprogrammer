#include <stdio.h>
#include <string.h>
#define NOTE_NUM 12

int selfedgeToIndex(char * name);
int noteToIndex(char * name);
char * getScaleNote(char * note, char * selfedge);

//TODO store notes in an index, write functions for retrieval
char * notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
char * selfedges[] = {"Do", "", "Re", "", "Mi", "Fa", "", "So", "La", "", "Ti"};

int main(){
   printf("%s\n", getScaleNote("C", "Do"));
   printf("%s\n", getScaleNote("C", "Re"));
   printf("%s\n", getScaleNote("C", "Mi"));
   printf("%s\n", getScaleNote("D", "Mi"));
   printf("%s\n", getScaleNote("A#", "Fa"));
}

int noteToIndex(char * note){
    for(int i = 0; i < 12; i++){
        if(strcmp(notes[i], note) == 0)
            return i;
    }
}

int selfedgeToIndex(char * note){
    for(int i = 0; i < 12; i++){
        if(strcmp(selfedges[i], note) == 0)
            return i;
    }
}

char * getScaleNote(char * note, char * selfedge){ 
    return notes[(noteToIndex(note)+selfedgeToIndex(selfedge))%NOTE_NUM];
}
