#include <ctime>

#include <iostream>
#include <deque>
#include <array>
using namespace std;

// Struct to represent a Sudoku board
struct SudokuBoard {
    int board[9][9];
    int steps; // Number of steps taken to reach this board state
};

// Function to check if the Sudoku board is solved
bool is_solved(int board[9][9]);

// Function to print the Sudoku board
void print_board(int board[9][9]);

void sleep(float n);
void sleep(float n)
{
    time_t t;
    time(&t);
    while(time(NULL)-t<n);

}
// Function to check if placing 'num' at board[row][col] is valid
bool is_valid(int board[9][9], int row, int col, int num) {
    // Check if the number is already in the row
    for (int i = 0; i < 9; ++i) {
        if (board[row][i] == num) {
            return false;
        }
    }
    
    // Check if the number is already in the column
    for (int i = 0; i < 9; ++i) {
        if (board[i][col] == num) {
            return false;
        }
    }
    
    // Check if the number is already in the 3x3 grid
    int start_row = 3 * (row / 3);
    int start_col = 3 * (col / 3);
    for (int i = start_row; i < start_row + 3; ++i) {
        for (int j = start_col; j < start_col + 3; ++j) {
            if (board[i][j] == num) {
                return false;
            }
        }
    }
    
    return true;
}

// Function to solve Sudoku using BFS
SudokuBoard solve_sudoku_bfs(int board[9][9]) 
{
    deque<SudokuBoard> queue; // Queue to store board states
    
    // Push the initial board state into the queue
    SudokuBoard initial_board;
    copy(&board[0][0], &board[0][0] + 9 * 9, &initial_board.board[0][0]);
    initial_board.steps = 0;
    queue.push_back(initial_board);
    
    while (!queue.empty()) {
        SudokuBoard current_board = queue.front();
        queue.pop_front();
        
        // Check if the current board is the solution
        if (is_solved(current_board.board)) {
            return current_board;
        }
        
        // Find the first empty cell
        int row, col;
        bool found_empty = false;
        for (row = 0; row < 9; ++row) {
            for (col = 0; col < 9; ++col) {
                if (current_board.board[row][col] == 0) {
                    found_empty = true;
                    break;
                }
            }
            if (found_empty) {
                break;
            }
        }
        
        // Try placing numbers in the empty cell
        for (int num = 1; num <= 9; ++num) {
            if (is_valid(current_board.board, row, col, num)) {
                // Make a copy of the current board and update it with the new number
                SudokuBoard new_board = current_board;
                new_board.board[row][col] = num;

                cout<<"UNSOLVED BOARD"<<endl;
                print_board(initial_board.board);
                cout<<endl<<endl<<"Solving..."<<endl;

                cout<<"Step "<<++new_board.steps<<":"<<endl;
                //
                print_board(new_board.board);
                // cout<<"\n\n";
                // sleep(0.01);
                system("clear");
                //
                // Push the new board state into the queue
                queue.push_back(new_board);
            }
        }
    }
    
    // If no solution is found, return an empty board
    return SudokuBoard();
}

// Function to check if the Sudoku board is solved
bool is_solved(int board[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Function to print the Sudoku board
void print_board(int board[9][9]) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Example Sudoku puzzle
int main() 
{
    


    int unsolved_board[9][9] = {
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

    cout << "Unsolved Sudoku:\n";
    print_board(unsolved_board);
    cout << endl;

    // time(&t);
    
    cout << "Solving...\n\n";

    SudokuBoard solved_board = solve_sudoku_bfs(unsolved_board);
 
    cout << "Unsolved Sudoku:\n";
    print_board(unsolved_board);
    cout << endl;
    if (is_solved(solved_board.board)) {
        cout << "Solved Sudoku:\n";
        print_board(solved_board.board);
        cout << "Steps: " << solved_board.steps << endl;
    } else {
        cout << "No solution exists\n";
    }

    return 0;
}