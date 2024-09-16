#include <iostream>
using namespace std;

const int SIDE = 3;  // Tic-tac-toe board size
const char HUMANMOVE = 'O';
const char COMPUTERMOVE = 'X';
const int COMPUTER = 1;
const int HUMAN = 0;

// Function to show the Tic-Tac-Toe board
void showBoard(char board[][SIDE]) {
    cout << "\t\t\t  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
    cout << "\t\t\t------------------------\n";
    cout << "\t\t\t  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
    cout << "\t\t\t------------------------\n";
    cout << "\t\t\t  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

// Function to initialize the board with '*'
void initialise(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            board[i][j] = '*';
        }
    }
}

// Show the instruction of the game
void showInstruction() {
    cout << "\nChoose a cell numbered from 1 to 9 as below and play\n\n";
    cout << "\t\t\t 1 | 2 | 3 \n";
    cout << "\t\t\t 4 | 5 | 6 \n";
    cout << "\t\t\t 7 | 8 | 9 \n";
}

// Check if any row is crossed with the same symbol
bool rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '*') {
            return true;
        }
    }
    return false;
}

// Check if any column is crossed with the same symbol
bool columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != '*') {
            return true;
        }
    }
    return false;
}

// Check if any diagonal is crossed with the same symbol
bool diagonalCrossed(char board[][SIDE]) {
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '*') {
        return true;
    }
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '*') {
        return true;
    }
    return false;
}

// Check if the game is over
bool gameOver(char board[][SIDE]) {
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

// Minimax algorithm to determine the best move for the computer
int minimax(char board[][SIDE], int depth, bool isAI) {
    int score = 0;
    int bestScore = 0;

    if (gameOver(board)) {
        if (isAI) {
            return -10;  // Human wins
        } else {
            return 10;   // Computer wins
        }
    }

    if (depth == SIDE * SIDE) {
        return 0;  // It's a tie
    }

    if (isAI) {
        bestScore = -999;  // Start with the lowest possible score
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                if (board[i][j] == '*') {
                    board[i][j] = COMPUTERMOVE;
                    score = minimax(board, depth + 1, false);
                    board[i][j] = '*';  // Undo the move
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        bestScore = 999;  // Start with the highest possible score
        for (int i = 0; i < SIDE; i++) {
            for (int j = 0; j < SIDE; j++) {
                if (board[i][j] == '*') {
                    board[i][j] = HUMANMOVE;
                    score = minimax(board, depth + 1, true);
                    board[i][j] = '*';  // Undo the move
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

// Function to determine the best move for the computer
int bestMove(char board[][SIDE], int moveIndex) {
    int x = -1, y = -1;
    int score = 0, bestScore = -999;

    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == '*') {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';  // Undo the move
                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * SIDE + y;
}

// Function to play the game of Tic-Tac-Toe
void playTicTacToe(int whoseTurn) {
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;

    initialise(board);
    showInstruction();

    while (gameOver(board) == false && moveIndex != SIDE * SIDE) {
        int n;
        if (whoseTurn == COMPUTER) {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            cout << "COMPUTER has put an " << COMPUTERMOVE << " in cell " << n + 1 << endl;
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        } else if (whoseTurn == HUMAN) {
            cout << "You can insert in the following positions: ";
            for (int i = 0; i < SIDE; i++) {
                for (int j = 0; j < SIDE; j++) {
                    if (board[i][j] == '*') {
                        cout << (i * 3 + j) + 1 << " ";
                    }
                }
            }
            cout << "\nEnter the position: ";
            cin >> n;
            n--;  // Adjust index to 0-based
            x = n / SIDE;
            y = n % SIDE;

            if (board[x][y] == '*' && n >= 0 && n < 9) {
                board[x][y] = HUMANMOVE;
                cout << "You have put an " << HUMANMOVE << " in cell " << n + 1 << endl;
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            } else if (board[x][y] != '*') {
                cout << "\nPosition is occupied! Choose another position.\n";
            } else {
                cout << "\nInvalid position! Try again.\n";
            }
        }
    }

    if (gameOver(board) == false && moveIndex == SIDE * SIDE) {
        cout << "It's a draw!\n";
    } else if (whoseTurn == COMPUTER) {
        cout << "Congratulations! You won!\n";
    } else {
        cout << "Computer wins!\n";
    }
}

// Main function
int main() {
    cout << "\n-----------------------------------------\n\n";
    cout << "Tic-Tac-Toe----------------\n";
    cout << "\n-----------------------------------------\n\n";

    char cont = 'y';

    do {
        char choice;
        cout << "Do you want to start first? (y/n): ";
        cin >> choice;

        if (choice == 'n') {
            playTicTacToe(COMPUTER);
        } else if (choice == 'y') {
            playTicTacToe(HUMAN);
        } else {
            cout << "Invalid choice\n";
        }

        cout << "\nDo you want to quit? (y/n): ";
        cin >> cont;

    } while (cont == 'n');

    return 0;
}

