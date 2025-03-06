#include <bits/stdc++.h>

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) {
                if (abs(row - i) == abs(col - j)) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

void printBoard(vector<vector<int>>& board, int n, int solutionNumber) {
    cout << "Solution " << solutionNumber << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] ? "Q " : ". ");
        }
        cout << endl;
    }
    cout << endl;
}

int solveNQueensAll(vector<vector<int>>& board, int row, int n, int& solutionCount) {
    // if finished?
    if (row == n) {
        solutionCount++;
        printBoard(board, n, solutionCount);
        return solutionCount;
    }
    
    for (int col = 0; col < n; col++) {
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1;
            
            solveNQueensAll(board, row + 1, n, solutionCount);
            
            //reset
            board[row][col] = 0;
        }
    }
    // no sulutions
    return solutionCount;
}

int main() {
    int n;
    cout << "N: ";
    cin >> n;
    
    vector<vector<int>> board(n, vector<int>(n, 0));
    int solutionCount = 0;
    
    int totalSolutions = solveNQueensAll(board, 0, n, solutionCount);
    
    if (totalSolutions == 0) {
        cout << "No solution exists." << endl;
    } else {
        cout << "Total: " << totalSolutions << endl;
    }
    
    return 0;
}