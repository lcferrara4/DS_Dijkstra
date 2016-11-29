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

bool operator<(const Grid_Pos& lhs, const Grid_Pos& rhs){
        return lhs.cost < rhs.cost;
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
    Grid_Pos position;

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

        char val;
        for( int i = 0; i < MAP_ROWS; i++ ){
            vector<char> temp;
            for( int j = 0; j < MAP_COLUMNS; j++ ){
                cin >> val;
                temp.push_back(val);
                position = {tiles[val], i, j};
                dist[position] = INT_MAX;
                prev[position] = position;
            }
            grid.push_back(temp);
        }
        cin >> RUNNER_START_ROW;
        cin >> RUNNER_START_COL;
        cin >> RUNNER_END_ROW;
        cin >> RUNNER_END_COL;

        priority_queue<Grid_Pos, vector<Grid_Pos> > frontier;
        set<Grid_Pos> marked;
        char name; int cost;
        int target_row = RUNNER_END_ROW;
        int target_col = RUNNER_END_COL;
        int total_cost = 0;
        name = grid[target_row][target_col];
        Grid_Pos next_position;
        marked.insert(position);
        //prev.push_back(position);
        dist[position] = 0;

        while( target_row != RUNNER_START_ROW || target_col != RUNNER_START_COL ){
            /* 
            priority_queue<Grid_Pos, vector<Grid_Pos> > pq;
            pq = frontier;
            while( !pq.empty() ){
                cout << pq.top().cost << " " << pq.top().row << " " << pq.top().col << endl;
                pq.pop();
            } 
            */
            for( int i = target_row - 1; i < target_row + 1; i++ ){
                for( int j = target_col - 1; j < target_col + 1; j++ ){
                    if( i >= 0 && i < MAP_ROWS && j >= 0 && j < MAP_COLUMNS && ( i == target_row ^ j == target_col) ){
                        name = grid[i][j];
                        cost = tiles[name];
                        next_position = {cost, i, j};
                        if( dist[position] + cost < dist[next_position] ){
                            dist[next_position] = dist[position] + cost;
                            prev[next_position] = position;
                            position = next_position;
                        }
                        frontier.push(next_position);          
                    }
                }   
            }
            while( !frontier.empty() && marked.find(frontier.top()) != marked.end() ){
                frontier.pop();
            }
            target_row = frontier.top().row;
            target_col = frontier.top().col;
            cost = frontier.top().cost;
            position = {cost, target_row, target_col};
            marked.insert(position);
        }  
        while( prev[position].row != position.row && prev[position].col != position.col ){
        
            total_cost += dist[position];
            position = prev[position];
        }
        cout << total_cost << endl;
    }
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
