#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

bool axisValid(int size, char ** board);

int main(){
    int n = 5;

    fstream boardFile("board_fail_1.txt");
    char ** board;
    board = new char *[n+1];
    for(int i = 0; i < n; i++){
        board[i] = new char[n+1];
    }

    if(boardFile.good()){
        for(int i = 0; i < n; i++){
            char line[n*2+1];
            line[0] = '\n';
            boardFile.getline(line, n*2+1);
            string parse(line);

            // Erase spaces and store
            parse.erase(remove(parse.begin(),parse.end(),' '), parse.end());
            sprintf(board[i], "%s", parse.c_str());
        }
    }
    for(int i = 0; i < n; i++){
        cout << board[i] << endl;
    }
    // char ** board;

    // cout << &board[0][0] << endl;
    // cout << &board[1][0] << endl;
    axisValid(n, board);

}


bool axisValid(int n, char ** board){
    for(int i = 2; i <= n; i++){
        for(int j = 0; j<=((n-1) - i + 1); j++){
            for(int k = 0; k<=((n-1) - i + 1); k++){
                cout << i << " " << j << " " << k << " ";
                cout << board[j][k] << endl;
            }
            cout << endl;
        }
    }
}