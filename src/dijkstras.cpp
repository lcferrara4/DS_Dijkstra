// dijsktras.cpp
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>
using namespace std;
// Main Execution
struct Grid_Pos{
    int cost;
    int row;
    int col;
};

class GridPos_Compare {
    public:
        bool operator()(Grid_Pos& lhs, Grid_Pos& rhs){
            if (lhs.cost > rhs.cost)
                return true;
            else
                return false;
        }
};

bool operator<(const Grid_Pos& lhs, const Grid_Pos& rhs){
    if( lhs.row == rhs.row ){
        return lhs.col < rhs.col;
    }
    return lhs.row < rhs.row;
}

bool operator==(const Grid_Pos& lhs, const Grid_Pos& rhs){
    return lhs.row == rhs.row && lhs.col == rhs.col;
}
bool operator!=(const Grid_Pos& lhs, const Grid_Pos& rhs){
    return lhs.row != rhs.row || lhs.col != rhs.col;
}

int main(int argc, char *argv[]) {
    
    // variables
    int TILE_N, MAP_ROWS, MAP_COLUMNS;
    int TILE_COST, RUNNER_START_ROW, RUNNER_START_COL, RUNNER_END_ROW, RUNNER_END_COL;
    char TILE_NAME;
    
    // need to store grid
    vector<vector<char>> grid;
    // need to store costs of different tiles
    map<char, int> tiles;

    while( cin >> TILE_N ){
        for( int i = 0; i < TILE_N; i++ ){
            cin >> TILE_NAME;
            cin >> TILE_COST;
            tiles.insert(pair<char,int>(TILE_NAME, TILE_COST));
        }

        cin >> MAP_ROWS;
        cin >> MAP_COLUMNS;

        // Initial Values
        map<Grid_Pos, int> dist;
        map<Grid_Pos, Grid_Pos> prev;
        Grid_Pos position;
        int count = 0;
        char val;
        for( int i = 0; i < MAP_ROWS; i++ ){
            vector<char> temp;
            for( int j = 0; j < MAP_COLUMNS; j++ ){
                cin >> val;
                temp.push_back(val);
                count++;
                position = {tiles[val], i, j};
                dist[position] = INT_MAX;
                prev[position] = {-1, -1, -1};
            }
            grid.push_back(temp);
        }
        cin >> RUNNER_START_ROW;
        cin >> RUNNER_START_COL;
        cin >> RUNNER_END_ROW;
        cin >> RUNNER_END_COL;

        priority_queue<Grid_Pos, vector<Grid_Pos>, GridPos_Compare> frontier;
        set< Grid_Pos > marked;
        char name; int cost;
        int target_row = RUNNER_END_ROW;
        int target_col = RUNNER_END_COL;
        int total_cost = 0;
        name = grid[target_row][target_col];
        position = {tiles[name], target_row, target_col};
        
        dist[position] = 0;

        Grid_Pos next_position;
        marked.insert(position);

        name = grid[RUNNER_START_ROW][RUNNER_START_COL];
        Grid_Pos start_position = { tiles[name], RUNNER_START_ROW, RUNNER_START_COL };

        while( marked.find(start_position) == marked.end() ){
           for( int i = target_row - 1; i <= target_row + 1; i++ ){
                for( int j = target_col - 1; j <= target_col + 1; j++ ){
                    if( i >= 0 && i < MAP_ROWS && j >= 0 && j < MAP_COLUMNS && ( i == target_row ^ j == target_col) ){
                        name = grid[i][j];
                        cost = tiles[name];
                        next_position = {cost, i, j};
                        //cout << "Current cost: " << dist[next_position] << endl;
                        //cout << "Possible cost: " << dist[position] + cost << endl;
                        if( dist[position] + cost < dist[next_position] && marked.find(next_position) == marked.end() ){
                            dist[next_position] = dist[position] + cost;
                            prev[next_position] = position;
                        }
                        frontier.push({dist[next_position], next_position.row, next_position.col});          
                    }
                }   
            }
            while( !frontier.empty() && marked.find(frontier.top()) != marked.end() ){
                frontier.pop();
            }
            /*
            priority_queue<Grid_Pos, vector<Grid_Pos>, GridPos_Compare> pq;
            cout << "Frontier:" << endl;
            pq = frontier;
            while(!pq.empty()){
                cout << pq.top().cost << " " << pq.top().row << " " << pq.top().col << endl;
                pq.pop();
            }
            */
            target_row = frontier.top().row;
            target_col = frontier.top().col;
            cost = frontier.top().cost;
            position = {cost, target_row, target_col};
            //cout << "Chosen: " << position.row << " " << position.col << endl;
            marked.insert(position);
        }  
        total_cost = dist[start_position];
        cout << total_cost << endl;
        while( prev[position].row != -1 && prev[position].col != -1 ){
            cout << position.row << " " << position.col << endl;
            position = prev[position];
        }
        cout << position.row << " " << position.col << endl;
    }
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
