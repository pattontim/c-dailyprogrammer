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

int main(){
    int n = 5;

    fstream boardFile("board_fail_1.txt");
    char ** board;
    board = new char *[n+1];
    for(int i = 0; i < n; i++){
        board[i] = new char[n+1];
    }

    // Parses input board to check for solutions
    if(boardFile.good()){
        for(int i = 0; i < n; i++){
            char line[n*2+1];
            line[0] = '\n';
            boardFile.getline(line, n*2+1);
            string parse(line);

            // Erase spaces and store
            parse.erase(remove(parse.begin(),parse.end(),' '), parse.end());
            cout << parse << endl;
            sprintf(board[i], "%s", parse.c_str());
        }
    }

    for(int i = 0; i < n; i++){
        cout << board[i] << endl;
    }

    // Conduct a test of the getBitAt function
    cout << "start: " << endl;
    int en = 7;
    for(int i = 0; i < en; i++){
        for(int j =0; j < en; j++){
            cout << getBitAt(17,i,j,en) << endl;
        }
    }
    cout << endl;

    // Uses a reflected binary code generator to search for an axis-valid board
    long int seq = -(pow(2,en*en));
    long int end = (pow(2,en*en));
    while(seq < end){
        if(axisValid(en, seq)){
            cout << "Answer found at: " << seq << endl;
            printIntAsBoard(seq, en);
            return 1;
        }
        seq++;
    }
    // cout << "solution number is: " << seq << endl;
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