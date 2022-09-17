#include <iostream>
#include <vector>
using namespace std;

#define en "\n"

string styles[3] = {"#o.", "# .", "Xo."}; // "<obstacle><free space><solution path>"
int styles_idx = 0;
bool fancy = 1;

void printMaze(int** pos, int row, int col){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if(fancy)
                cout << styles[styles_idx][pos[i][j]] << ' ';
            else
                cout << pos[i][j] << ' ';
        }
        cout << en;
    }
}

int getDirChange(vector<pair<int, int>> &path){
    int p_size = path.size();
    if(p_size <= 2)
        return 0;
    
    int dir_change = 0;
    int ch_xp, ch_yp, ch_x, ch_y;

    // check from second to second last points
    for(int i = 1; i < p_size-1; i++){
        ch_xp = path[i].first - path[i-1].first;
        ch_yp = path[i].second - path[i-1].second;
        ch_x = path[i+1].first - path[i].first;
        ch_y = path[i+1].second - path[i].second;
        
        if(ch_xp != ch_x || ch_yp != ch_y)
            dir_change++;
    }
    return dir_change;
}

int compareDirChange(vector<pair<int, int>> &path, vector<vector<pair<int, int>>> &new_sol, int min_dir_change){
    // compare direction change of current path with the new_solutions
    // to get best of the best solutions
    int dir_change = getDirChange(path);
    if(new_sol.size()){
        if(dir_change == min_dir_change){
            new_sol.push_back(path);
            return min_dir_change;
        }else if(dir_change < min_dir_change){
            new_sol.clear();
            new_sol.push_back(path);
            return dir_change;
        }
        return min_dir_change;
    }else{
        new_sol.push_back(path);
        return dir_change;
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

void compare(vector<pair<int, int>> &path, vector<vector<pair<int, int>>> &sol){
    // compare size of current path with the solutions
    // to get smaller/best solutions
    if(sol.size()){
        int sol_min_size = sol[0].size();

        if (path.size() == sol_min_size){
            sol.push_back(path);
        }else if(path.size() < sol_min_size){
            sol.clear();
            sol.push_back(path);
        }
    }else
        sol.push_back(path);
}

void solveMaze(int** pos, int row, int col, int x, int y, int en_x, int en_y, vector<pair<int, int>> &path, vector<vector<pair<int, int>>> &sol){
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
    int row, col, max_solve;
    cin >> row >> col >> max_solve;

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

    // cout << en;
    // printMaze(pos, row, col);
    
    vector<pair<int, int>> path;
    vector<vector<pair<int, int>>> sol;

    // validate start & end point
    if(!(isSafe(pos, row, col, st_x, st_y, path) && isSafe(pos, row, col, en_x, en_y, path))){
        cout << en << -1 << en;
        return 0;
    }

    solveMaze(pos, row, col, st_x, st_y, en_x, en_y, path, sol);

    int min_dir_change = INT_MAX;
    vector<vector<pair<int, int>>> new_sol;
    for(auto i: sol)
        min_dir_change = compareDirChange(i, new_sol, min_dir_change);

    if(new_sol.size()){
        // <number of solutions> <steps taken> <minimum direction change>
        cout << en << new_sol.size() << ' ' << new_sol[0].size() << ' ' << min_dir_change << en << en;

        for(int i = 0; i < new_sol.size() && (max_solve == -1 || i < max_solve); i++){
            // add new_sol[i] to pos
            for(auto j: new_sol[i])
                pos[j.first][j.second] = 2;
            
            // output maze
            printMaze(pos, row, col);
            cout << en;
            
            // remove current new_sol[i] from pos
            for(auto j: new_sol[i])
                pos[j.first][j.second] = 1;
        }
    }else
        cout << en << 0 << en;
}
