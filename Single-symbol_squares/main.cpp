#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main(){
    int n = 5;

    fstream boardFile("board_fail_1.txt");
    char board [n+1][n+1];

    if(boardFile.good()){
        boardFile >> ws;
        string line;
        for(int i = 0; i <= n; i++){
            // stringstream line;
            boardFile.getline(board[i], n+1);
            // line >> ws;
            stringstream line(board[i]);
            line >> ws;
            // board[i] ;
            // board[i] << line;
        }
    }
    for(int i = 0; i <= n; i++){
        cout << board[i] << endl;
    }

}