Calculates if a board is 'axis valid'.

input: a positive integer n
output: a board of size n*n that is axis-valid

to compile: g++ main.cpp -o symbols.o
to test: 
./symbols.o 5
Answer found at: -33220059
10100
10001
01100
01010
00000

### Considerations

Known Issues:

TODO
- Implement randomization of board generation
- Update algorithm to support boards beyond size 6
- Pretty print the board

Debugging

Test functions for getting bits:
// Conduct a test of the getBitAt function
    cout << "start: " << endl;
    int en = 6;
    for(int i = 0; i < en; i++){
        for(int j =0; j < en; j++){
            cout << getBitAt(17,i,j,en) << endl;
        }
    }
    cout << endl;

Board printing functions:
// fstream boardFile("board_fail_1.txt");
    // char ** board;
    // board = new char *[n+1];
    // for(int i = 0; i < n; i++){
    //     board[i] = new char[n+1];
    // }

    // Parses input board to check for solutions
    // if(boardFile.good()){
    //     for(int i = 0; i < n; i++){
    //         char line[n*2+1];
    //         line[0] = '\n';
    //         boardFile.getline(line, n*2+1);
    //         string parse(line);

    //         // Erase spaces and store
    //         parse.erase(remove(parse.begin(),parse.end(),' '), parse.end());
    //         cout << parse << endl;
    //         sprintf(board[i], "%s", parse.c_str());
    //     }
    // }

    // for(int i = 0; i < n; i++){
    //     cout << board[i] << endl;
    // }