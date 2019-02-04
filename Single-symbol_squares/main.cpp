// Created by Timothy Patton on December 24, 2019 for the purposes
// of generating axis-valid boards according to the daily programmer challenge.
// You may view the challenge here: https://www.reddit.com/r/dailyprogrammer/comments/9z3mjk/20181121_challenge_368_intermediate_singlesymbol/
// Works up to n=6

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <climits>
#include <math.h>

using namespace std;

bool axisValid(int size, long int seq);
bool axisValid(int size, char ** board);
bool getBitAt(long int b, int i, int j, int n);
void printIntAsBoard(long int seq, int n);

int main(int argc, char *argv[]){
    int n = 0;

    if(argc < 2){
        cout << "Please provide a board size." << endl;
        exit(1);
    }
    
    istringstream(argv[1]) >> n;

    // Uses a reflected binary code generator to search for an axis-valid board
    long int seq = -(pow(2,n*n));
    long int end = (pow(2,n*n));
    while(seq < end){
        if(axisValid(n, seq)){
            cout << "Answer found at: " << seq << endl;
            printIntAsBoard(seq, n);
            break;
        }
        seq++;
    }
}

// Returns if a bit is on starting from the rightmost location and taking row dominant values as i/j
// For example, a, b and c are the 0-th, 4-th, and 7-th bit in this implementation
//       c  b   a
// 10101101010101
bool getBitAt(long int b, int i, int j, int n){
    if(i>n || j>n){
        return __throw_out_of_range;
    }
    // cout << "start: " << std::bitset<4>(b).to_string() << endl; //to binary
    // cout << "end: " << std::bitset<4>(b >> ((n*i + j))).to_string() << endl; //to binary
    // cout << "Offset value: " << (((n*i + j))) << endl;
    return (b >> (((n*i) + j))) & 1;
}

void printIntAsBoard(long int seq, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << getBitAt(seq,i,j,n);
        }
        cout << endl;
    }
}

bool axisValid(int n, long int seq){
    for(int i = 2; i <= n; i++){
        for(int j = 0; j<=((n-1) - i + 1); j++){
            for(int k = 0; k<=((n-1) - i + 1); k++){
                // Check the four corners of the board
                if(getBitAt(seq, j, k, n) == getBitAt(seq, j, k+(i-1), n) 
                && getBitAt(seq, j, k, n) == getBitAt(seq, j+(i-1), k, n)
                && getBitAt(seq, j, k, n) == getBitAt(seq, j+(i-1), k+(i-1), n)){
                    return false;
                }
            }
            // cout << endl;
        }
    }
    return true;
}

bool axisValid(int n, char ** board){
    for(int i = 2; i <= n; i++){
        for(int j = 0; j<=((n-1) - i + 1); j++){
            for(int k = 0; k<=((n-1) - i + 1); k++){
                // Check the four corners of the board
                if(board[j][k] == board[j][k+(i-1)] 
                && board[j][k] == board[j+(i-1)][k] 
                && board[j][k] == board[j+(i-1)][k+(i-1)]){
                    return false;
                }
            }
            // cout << endl;
        }
    }
    return true;
}