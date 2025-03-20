#include <iostream>
#include <vector>

using namespace std;

const int N = 9;

void printSudoku(vector<vector<int>>& matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

bool isValid(vector<vector<int>>& sudoku, int row, int col, int num) {
    for (int o = 0; o < N; o++) {
        if (sudoku[row][o] == num) {
            return false;
        }
    }

    for (int s = 0; s < N; s++) {
        if (sudoku[s][col] == num) {
            return false;
        }
    }

    int rt_row = row - row % 3;
    int rt_col = col - col % 3;

    for (int i = rt_row; i < rt_row + 3; i++) {
        for (int j = rt_col; j < rt_col + 3; j++) {
            if (sudoku[i][j] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& sudoku, int row, int col) {
    if (row == N - 1 && col == N) {
        return true;
    }

    if (col == N) {
        row++;
        col = 0;
    }

    if (sudoku[row][col] > 0) {
        return solveSudoku(sudoku, row, col + 1);
    }

    for (int num = 1; num <= N; num++) {
        if (isValid(sudoku, row, col, num)) {
            sudoku[row][col] = num;
            
            if (solveSudoku(sudoku, row, col + 1)) {
                return true;
            }
        }
        sudoku[row][col] = 0;
    }
    return false;
}

int main() {
    vector<vector<int>> sudoku = {
        { 5, 0, 0, 0, 4, 0, 7, 0, 3 },
        { 0, 4, 0, 6, 2, 8, 0, 0, 0 },
        { 0, 0, 2, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 5, 0, 0, 4, 9, 7 },
        { 0, 0, 0, 0, 7, 0, 0, 0, 0 },
        { 7, 1, 4, 0, 0, 3, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 6, 0, 0 },
        { 0, 0, 0, 9, 6, 2, 0, 5, 0 },
        { 8, 0, 1, 0, 3, 0, 0, 0, 9 }
    };

    if (solveSudoku(sudoku, 0, 0)) {
        printSudoku(sudoku);
    } else {
        cout << "No solution found..." << endl;
    }

    return 0;
}