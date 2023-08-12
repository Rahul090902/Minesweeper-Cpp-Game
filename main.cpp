#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int ROWS = 8;
const int COLS = 8;
const int MINES = 10;

struct Cell {
    bool isMine;
    bool isRevealed;
    int adjacentMines;
};

vector<vector<Cell>> board(ROWS, vector<Cell>(COLS));

void initializeBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j].isMine = false;
            board[i][j].isRevealed = false;
            board[i][j].adjacentMines = 0;
        }
    }

    // Place mines randomly
    for (int m = 0; m < MINES; ++m) {
        int randRow, randCol;
        do {
            randRow = rand() % ROWS;
            randCol = rand() % COLS;
        } while (board[randRow][randCol].isMine);

        board[randRow][randCol].isMine = true;

        // Update adjacent cells
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int newRow = randRow + i;
                int newCol = randCol + j;
                if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
                    board[newRow][newCol].adjacentMines++;
                }
            }
        }
    }
}

void revealCell(int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS || board[row][col].isRevealed) {
        return;
    }

    board[row][col].isRevealed = true;

    if (board[row][col].isMine) {
        cout << "Game Over! You hit a mine!" << endl;
        exit(0);
    }

    if (board[row][col].adjacentMines == 0) {
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                revealCell(row + i, col + j);
            }
        }
    }
}

void displayBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j].isRevealed) {
                if (board[i][j].isMine) {
                    cout << "* ";
                } else {
                    cout << board[i][j].adjacentMines << " ";
                }
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    initializeBoard();

    while (true) {
        displayBoard();

        int row, col;
        cout << "Enter row and column (0-based): ";
        cin >> row >> col;

        revealCell(row, col);
    }

    return 0;
}

