#include <iostream>
#include <vector>
#include <map>

#define N 9 // Size of the Sudoku grid (9x9)

bool areAllMapsEmpty(std::map<int, std::map<int, std::vector<int>>>& outerMap) {
        for (const auto& outerPair : outerMap) {
            const std::map<int, std::vector<int>>& innerMap = outerPair.second;
            for (const auto& innerPair : innerMap) {
                const std::vector<int> constraint = innerPair.second;
                if (!constraint.empty()) {
                    return false;  // Found a non-empty map
                }
            }
        }
    return true;  // All maps are empty
}

// Function to print the Sudoku board
void printBoard(const std::vector<std::vector<int>>& board) {
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            std::cout << board[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number can be placed in a specific cell
bool isSafe(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check row and column for the number
    for (int x = 0; x < N; ++x) {
        if (board[row][x] == num || board[x][col] == num) {
            return false;
        }
    }

    // Check the 3x3 sub-grid for the number
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

std::map<int, std::map<int, std::vector<int>>> createConstraints(std::vector<std::vector<int>>& board){

    std::map<int, std::map<int, std::vector<int>>> result;

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            if (board[row][col] != 0){
                result[row][col] = std::vector<int>();
            }
            else{
                std::vector<int> constraints;
                for (int num = 1; num < N+1; ++num){
                    if (isSafe(board, row, col, num)){
                        constraints.push_back(num);
                    }
                }
                result[row][col] = constraints;
            }
        }
    }

    return result;

}

bool nakedSingles(std::vector<std::vector<int>>& board, std::map<int, std::map<int, std::vector<int>>>& constraints){
    bool result = false;
    
    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            std::vector<int> cons = constraints[row][col];
            if (cons.size() == 1){
                board[row][col] = cons[0];
                result = true;
            }
        }
    }

    if (result){
        constraints = createConstraints(board);
    }

    return result;

}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& board) {
    int row, col;
    bool emptyFound = false;

    // Find an empty cell
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (board[row][col] == 0) {
                emptyFound = true;
                break;
            }
        }
        if (emptyFound) break;
    }

    // If there are no empty cells, the puzzle is solved
    if (!emptyFound) return true;

    // Try placing numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num; // Place the number

            // Recursively solve the rest of the board
            if (solveSudoku(board)) return true;

            board[row][col] = 0; // Backtrack if the placement did not lead to a solution
        }
    }

    return false; // Trigger backtracking
}

bool solveSudokuHuman(std::vector<std::vector<int>>& board) {

    std::map<int, std::map<int, std::vector<int>>> constraints = createConstraints(board);

    bool step = true;

    while (!areAllMapsEmpty(constraints) & step){
        step = nakedSingles(board, constraints);
        printBoard(board);
        std::cout << std::endl;
    }

    return step;
}

int main() {
    // Example Sudoku puzzle (0 represents an empty cell)
    std::vector<std::vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudokuHuman(board)) {
        std::cout << "Sudoku solved successfully:\n";
        printBoard(board);
    } else {
        std::cout << "No solution exists.\n";
        printBoard(board);
    }

    return 0;
}
