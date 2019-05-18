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
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

// Generate a lookup table for 32bit operating system  
// using macro  
#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64 
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16) 
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 ) 

// Lookup table that store the reverse of each table 
unsigned int lookuptable[256] = { R6(0), R6(2), R6(1), R6(3) }; 
  
/* Function to reverse bits of num */
int reverseBits(unsigned int num) 
{ 
    int reverse_num = 0; 
  
     // Reverse and then rearrange  
  
                   // first chunk of 8 bits from right 
     reverse_num = lookuptable[ num & 0xff ]<<24 |  
  
                   // second chunk of 8 bits from  right  
                   lookuptable[ (num >> 8) & 0xff ]<<16 |  
  
                   lookuptable[ (num >> 16 )& 0xff ]<< 8 | 
                   lookuptable[ (num >>24 ) & 0xff ] ; 
    
    return reverse_num; 
} 

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

    // prior cooking TODO
    long int end, seq, start;
    srand(time(NULL));

    // how to limit by number of X's and O's...
    // You must be able to limit it by related to which numbers cause a large amount
    // of bits to be turned off or on.
    // ex are both large but have few bits on
    // 100000000 versus 100000001
    // if a number is mod-able by 1,2,4,8,... then it has a bit on.
    // select between 10 and 22 bits to be on, ie generate 4 random
    // problem is not in generation but in the checking, so we can reject numbers that
    // are not modable by at least 10 or 22 digits, converts n^2 to less, maybe nlogn?
    // could I increment or start the counter so as to generate #s with lots of 0's/1's?
    // there must be!

    // double twotimes = (double)2*INT_MAX;
    // cout << (__DBL_MAX__/2 == 2*INT_MAX) << endl;
    // cout << INT_MAX << " " << twotimes << endl;
    end = (pow(2,n*n));
    start = -(pow(2,n*n));

    // start = rand() % (int)((double)2*end) - end;
    seq = start;
    cout << "Start: " << start << endl;
    
    while(seq < end){
        if(axisValid(n, seq)){
            cout << "Answer found at: " << seq << endl;
            printIntAsBoard(seq, n);
            break;
        }
        seq++;
    }
    // seq=start;
    // while(seq > -end){
    //     if(axisValid(n, seq)){
    //         cout << "Answer found at: " << seq << endl;
    //         printIntAsBoard(seq, n);
    //         break;
    //     }
    //     seq--;
    // }
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