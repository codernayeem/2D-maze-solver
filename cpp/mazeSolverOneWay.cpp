#include <iostream>
using namespace std;

string styles[3] = {"#o.", "# .", "Xo."}; // "<obstacle><free space><solution path>"
int styles_idx = 0;

void printMaze(int** pos, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++)
            cout << pos[i][j] << ' ';
        cout << endl;
    }
}

void printMazeFancy(int** pos, int row, int col, string chars){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){

            if(pos[i][j] == 1 || pos[i][j] == 2)
                cout << chars[pos[i][j]];
            else
                cout << chars[0];
            
            cout << ' ';
        }
        cout << endl;
    }
}

bool isSafe(int** pos, int row, int col, int x, int y){
    return (x >= 0 && y >= 0 && x < row && y < col && pos[x][y] == 1);
}

bool solveMaze(int** pos, int row, int col, int x, int y, int en_x, int en_y){
    // base
    if (x == en_x && y == en_y){
        pos[x][y] = 2;
        return true;
    }
    
    if (isSafe(pos, row, col, x, y)){
        pos[x][y] = 2;

        // check every direction to solve
        if(solveMaze(pos, row, col, x+1, y, en_x, en_y) || solveMaze(pos, row, col, x, y+1, en_x, en_y) || solveMaze(pos, row, col, x-1, y, en_x, en_y) || solveMaze(pos, row, col, x, y-1, en_x, en_y))
            return true;
        
        pos[x][y] = 1;  // backtracking
    }
    return false;
}

int main(){
    int row, col;
    cin >> row >> col;

    // x -> row no | y -> col no
    int st_x = 1, st_y = 1;     // start row, col
    int en_x = row, en_y = col; // finish row, col

    cin >> st_x >> st_y >> en_x >> en_y;
    st_x --; st_y --; en_x--; en_y--; // row, col --> row_idx, col_idx

    // save input in heap
    int** pos = new int*[row];
    for (int i = 0; i < row; i++){
        pos[i] = new int[col];
        for (int j = 0; j < col; j++){
            cin >> pos[i][j];
        }
    }
    
    // cout << "\n";
    // printMazeFancy(pos, row, col, styles[0]);
    
    cout << "\n";
    // validate start & end point
    if(!(isSafe(pos, row, col, st_x, st_y) && isSafe(pos, row, col, en_x, en_y))){
        cout << -1 << "\n";
        return 0;
    }

    if(solveMaze(pos, row, col, st_x, st_y, en_x, en_y)){
        // printMaze(pos, row, col);
        printMazeFancy(pos, row, col, styles[styles_idx]);
    }else
        cout << 0; // No way to solve
    cout << "\n";
}
