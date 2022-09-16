#include <iostream>
#include <vector>
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

bool isSafe(int** pos, int row, int col, int x, int y, vector<pair<int, int>> &path){
    if(x >= 0 && y >= 0 && x < row && y < col && pos[x][y] == 1){
        for(auto i: path){
            if (i.first == x && i.second == y) // check if already occupied
                return false;
        }
        return true;
    }
    return false;
}

void compare(vector<pair<int, int>> &path, vector<pair<int, int>> &sol){
    // compare size of current path with the solution
    // to get smaller solution
    if(sol.size() == 0 || path.size() < sol.size())
        sol = path;
}

void solveMaze(int** pos, int row, int col, int x, int y, int en_x, int en_y, vector<pair<int, int>> &path, vector<pair<int, int>> &sol){
    // base
    if (x == en_x && y == en_y){
        path.push_back(make_pair(x, y));
        compare(path, sol);
        path.pop_back();
        return;
    }

    if (isSafe(pos, row, col, x, y, path)){
        path.push_back(make_pair(x, y));

        solveMaze(pos, row, col, x+1, y, en_x, en_y, path, sol);
        solveMaze(pos, row, col, x, y+1, en_x, en_y, path, sol);
        solveMaze(pos, row, col, x-1, y, en_x, en_y, path, sol);
        solveMaze(pos, row, col, x, y-1, en_x, en_y, path, sol);
        
        path.pop_back(); // backtracking
    }
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
    vector<pair<int, int>> path, sol;

    // validate start & end point
    if(!(isSafe(pos, row, col, st_x, st_y, path) && isSafe(pos, row, col, en_x, en_y, path))){
        cout << -1 << "\n";
        return 0;
    }

    solveMaze(pos, row, col, st_x, st_y, en_x, en_y, path, sol);
    cout << "\n" << sol.size() << "\n\n"; // print step
    if(sol.size()){
        // add sol to pos
        for(auto i: sol)
            pos[i.first][i.second] = 2;

        // output maze
        // printMaze(pos, row, col);
        printMazeFancy(pos, row, col, styles[styles_idx]);
        cout << '\n';
    }
}
