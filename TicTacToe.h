#include <iostream>
#include <string>
#include <windows.h>
#include <limits>
#undef max
using namespace std;

class TicTacToe {
    public:
        TicTacToe() {
            char symbol = '1';
            for (int i = 0; i < 9; i++) {
                boardSymbols[i] = symbol;
                symbol++;
            }
        }
        void play() {
            drawBoard();
            string mode = "";
            string player = "";
            string opponent = "";
            cout << "Type the mode to play against (player or computer): ";
            cin >> mode;
            while (mode != "player" && mode != "computer") {
                cout << "\nPlease type in a valid mode: ";
                cin >> mode;
            }
            cout << "Choose O or X to start: ";
            cin >> player;
            while (player.length() != 1 || (player[0] != 'O' && player[0] != 'X')) {
                cout << "\nPlease type in the correct character: ";
                cin >> player;
            }
            // setting up player symbols
            if (player[0] == 'O') {
                opponent = "X";
            }      
            if (player[0] == 'X') {
                opponent = "O";
            }     
            // starting the game
            if (mode == "player") {
                playerMode(player[0], opponent[0]);
            }
            if (mode == "computer") {
                computerMode(player[0], opponent[0]);
            }
        }
    private:
        void playerMode(char p1, char p2) {
            int moveCount = 0; // keeps track of the current total number of moves
            int selectedNum = 0;
            char currPlayer = p1;
            char nextPlayer = p2;
            // while neither p1 and p2 have won and the game has not ended
            while (getResult(p1, p2) != 1 && getResult(p1, p2) != 2 && moveCount <= 8) {
                cout << "\nChoose a number on the board (" << currPlayer << "'s turn): ";
                cin >> selectedNum;
                while (!(selectedNum >= 1 && selectedNum <= 9)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nPlease type in a valid number: ";
                    cin >> selectedNum;
                }             
                if (boardSymbols[selectedNum - 1] != nextPlayer && boardSymbols[selectedNum - 1] != currPlayer) {
                    boardSymbols[selectedNum - 1] = currPlayer;
                    drawBoard();
                    moveCount++;
                    if (currPlayer == p1) { // alternate turns
                        currPlayer = p2;
                        nextPlayer = p1;
                    }
                    else if (currPlayer == p2) { // alternate turns
                        currPlayer = p1;
                        nextPlayer = p2;
                    }                   
                }
                else {
                    cout << "\n- Number already chosen, choose another number. " << endl;
                }
                getResult(p1, p2);                
            }
            if (getResult(p1, p2) == 1) {
                cout << "Player " << p1 << " wins!" << endl;
            }
            else if (getResult(p1, p2) == 2) {
                cout << "Player " << p2 << " wins!" << endl;
            }
            else if (getResult(p1, p2) == 0 && moveCount > 8) {
                cout << "Draw!" << endl;
            }
        
        }
        void computerMode(char p1, char p2) {
            int moveCount = 0;
            int selectedNum = 0;
            while (getResult(p1, p2) != 1 && getResult(p1, p2) != 2 && moveCount <= 8) { 
                cout << "\nChoose a number on the board (" << p1 << "'s turn): ";
                cin >> selectedNum;                
                while (!(selectedNum >= 1 && selectedNum <= 9)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\nPlease type in a valid number: ";
                    cin >> selectedNum;

                }  
                if (boardSymbols[selectedNum - 1] != p2 && boardSymbols[selectedNum - 1] != p1) {
                    boardSymbols[selectedNum - 1] = p1;
                    drawBoard();
                    moveCount++;
                }
                else {
                    while (boardSymbols[selectedNum - 1] == p2 || boardSymbols[selectedNum - 1] == p1) {
                        cout << "Number already chosen, choose another number: ";
                        cin >> selectedNum;
                        // check the validity of the new input number
                        while (!(selectedNum >= 1 && selectedNum <= 9)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\nPlease type in a valid number: ";
                            cin >> selectedNum;
                        }  
                    }  
                    boardSymbols[selectedNum - 1] = p1;
                    drawBoard();
                    moveCount++;   
                }
                if (moveCount <= 8) {
                    makeMove(p1, p2); 
                    moveCount++;
                    cout << p2 << "'s turn: " << endl;
                    Sleep(1200); // delay of 1.2 seconds to distinguish player moves from computer moves
                    drawBoard();   
                }        
                getResult(p1, p2); 
            }
            if (getResult(p1, p2) == 1) {
                cout << "Player " << p1 << " wins!" << endl;
            }
            else if (getResult(p1, p2) == 2) {
                cout << "Player " << p2 << " wins!" << endl;
            }
            else if (getResult(p1, p2) == 0 && moveCount > 8) {
                cout << "Draw!" << endl;
            }
        }
        void makeMove(char pSymbol, char cSymbol) {
            // check if the computer can win in the next move
            for (int i = 0; i < 9; i++) {
                if (boardSymbols[i] != pSymbol && boardSymbols[i] != cSymbol) {
                    char temp = boardSymbols[i];
                    boardSymbols[i] = cSymbol;
                    if (checkWin(cSymbol)) {
                        return;
                    }
                    else {
                        boardSymbols[i] = temp;
                    }
                }
            }
            // if the computer cannot win in the next move, block the player's winning moves
            for (int i = 0; i < 9; i++) {
                if (boardSymbols[i] != pSymbol && boardSymbols[i] != cSymbol) {
                    char temp = boardSymbols[i];
                    boardSymbols[i] = pSymbol;
                    if (checkWin(pSymbol)) {
                        boardSymbols[i] = cSymbol;
                        return;
                    }
                    else {
                        boardSymbols[i] = temp;
                    }
                }
            }
            // if the computer cannot win or block, make a strategic move
            if (boardSymbols[4] != pSymbol && boardSymbols[4] != cSymbol) { // pick the middle if it is available
                boardSymbols[4] = cSymbol;
                return;
            }
            for (int i = 0; i < 9; i += 2) { // if the middle is not available, pick a corner
                if (boardSymbols[i] != pSymbol && boardSymbols[i] != cSymbol) {
                    boardSymbols[i] = cSymbol;
                    break;
                }     
            } 
        }
        bool checkWin(char symbol) {
            // checking rows
            for (int i = 0; i < 9; i += 3) {
                if (boardSymbols[i] == symbol && boardSymbols[i+1] == symbol && boardSymbols[i+2] == symbol) {
                    return true;
                }
            }
            // checking columns
            for (int i = 0; i < 3; i++) {
                if (boardSymbols[i] == symbol && boardSymbols[i+3] == symbol && boardSymbols[i+6] == symbol) {
                    return true;
                }
            }
            // checking diagonals
            if ((boardSymbols[0] == symbol && boardSymbols[4] == symbol && boardSymbols[8] == symbol) || 
                (boardSymbols[2] == symbol && boardSymbols[4] == symbol && boardSymbols[6] == symbol)) {
                return true;
            } 
            return false;
        }
        int getResult(char p1, char p2) {
            int value = 0; // value to determine winner
            // checking rows
            for (int i = 0; i < 9; i += 3) {
                if (boardSymbols[i] == p1 && boardSymbols[i+1] == p1 && boardSymbols[i+2] == p1) {
                    value = 1;
                    break;
                }
                if (boardSymbols[i] == p2 && boardSymbols[i+1] == p2 && boardSymbols[i+2] == p2) {
                    value = 2;
                    break;
                }
            }
            // checking columns
            for (int i = 0; i < 3; i++) {
                if (boardSymbols[i] == p1 && boardSymbols[i+3] == p1 && boardSymbols[i+6] == p1) {
                    value = 1;
                    break;
                }
                if (boardSymbols[i] == p2 && boardSymbols[i+3] == p2 && boardSymbols[i+6] == p2) {
                    value = 2;
                    break;
                }
            }
            // checking diagonals
            if ((boardSymbols[0] == p1 && boardSymbols[4] == p1 && boardSymbols[8] == p1) || 
                (boardSymbols[2] == p1 && boardSymbols[4] == p1 && boardSymbols[6] == p1)) {
                value = 1;           
            }
            if ((boardSymbols[0] == p2 && boardSymbols[4] == p2 && boardSymbols[8] == p2) || 
                (boardSymbols[2] == p2 && boardSymbols[4] == p2 && boardSymbols[6] == p2)) {
                value = 2;       
            }
            return value;            
        }
        void drawBoard() {
            cout << "       |       |       " << endl;
            cout << "   " << boardSymbols[0] << "   |   " << boardSymbols[1] << "   |   " << boardSymbols[2] << endl;
            cout << "_______|_______|_______" << endl;
            cout << "       |       |        " << endl;
            cout << "   " << boardSymbols[3] << "   |   " << boardSymbols[4] << "   |   " << boardSymbols[5] << endl;
            cout << "_______|_______|_______" << endl;        
            cout << "       |       |       " << endl;
            cout << "   " << boardSymbols[6] << "   |   " << boardSymbols[7] << "   |   " << boardSymbols[8] << endl;
            cout << "       |       |       " << endl << endl;                  
        }
        char boardSymbols[9];
};