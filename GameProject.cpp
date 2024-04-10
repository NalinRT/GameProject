#include<bits/stdc++.h>
using namespace std;
const int N1 = 9;
bool isValid(vector<vector<int>>& board, int row, int col, int num) {
    // Check if num exists in row
    for (int i = 0; i < N1; ++i)
        if (board[row][i] == num)
            return false;
    
    // Check if num exists in col
    for (int i = 0; i < N1; ++i)
        if (board[i][col] == num)
            return false;
    
    // Check if num exists in current 3x3 grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i + startRow][j + startCol] == num)
                return false;
    
    return true;
}

bool solveSudoku(vector<vector<int>>& board) {
    int row, col;
    
    // Find empty cell
    bool found = false;
    for (row = 0; row < N1; ++row) {
        for (col = 0; col < N1; ++col) {
            if (board[row][col] == 0) {
                found = true;
                break;
            }
        }
        if (found)
            break;
    }
    
    // If no empty cell found, puzzle is solved
    if (!found)
        return true;
    
    // Try different numbers in current cell
    for (int num = 1; num <= 9; ++num) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board))
                return true;
            board[row][col] = 0; // backtrack
        }
    }
    
    return false;
}

void printSudoku(vector<vector<int>>& board) {
    for (int i = 0; i < N1; ++i) {
        for (int j = 0; j < N1; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void sudoku() {
    vector<vector<int>>board(9,vector<int>(9,0));
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cin>>board[i][j];
        }
    }
    if (solveSudoku(board))
        printSudoku(board);
    else
        cout << "No solution exists" << endl;
}

// Define directions (up, right, down, left)
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

bool isValid2(vector<vector<int>> &maze, int x, int y, int n) {
    return (x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == 0);
}

void printPath(stack<pair<int, int>>& path) {
    while (!path.empty()) {
        pair<int, int> point = path.top();
        path.pop();
        cout << "(" << point.first << ", " << point.second << ") ";
    }
    cout << endl;
}

bool solveMaze(vector<vector<int>> &maze, int startX, int startY, int endX, int endY, int n) {
    stack<pair<int, int>> path;
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    path.push({startX, startY});
    visited[startX][startY] = true;

    while (!path.empty()) {
        pair<int, int> current = path.top();
        int x = current.first;
        int y = current.second;
        path.pop();

        // Check if reached the end
        if (x == endX && y == endY) {
            cout << "Path found: ";
            printPath(path);
            return true;
        }

        // Explore in all directions
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid2(maze, newX, newY, n) && !visited[newX][newY]) {
                path.push({newX, newY});
                visited[newX][newY] = true;
            }
        }
    }

    cout << "No path found!" << endl;
    return false;
}

void mazeSolver() {
    int n;
    cin>>n;
    vector<vector<int>>maze(n,vector<int>(n,0));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>maze[i][j];
        }
    }
    int startX = 0, startY = 0; // Starting point
    int endX = n-1, endY = n-1; // Ending point

    cout << "Maze:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Start point: (" << startX << ", " << startY << ")" << endl;
    cout << "End point: (" << endX << ", " << endY << ")" << endl;

    cout << "Finding path..." << endl;
    solveMaze(maze, startX, startY, endX, endY, n);
}

// More Games can be added

int main()
{
    int n;
    while(1)
    {
        cout<<"1. Sudoku/n2. Maze\nEnter your choice:";
        cin>>n;
        if(n==1)
        sudoku();
        else if(n==2)
        mazeSolver();
        else
        break;
    }
    return 0;
}
