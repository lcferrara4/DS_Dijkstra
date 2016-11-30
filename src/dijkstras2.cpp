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
    pair<int, int> pos;
    int cost;
};

bool operator<(const Grid_Pos& lhs, const Grid_Pos& rhs){
        return lhs.cost > rhs.cost; // flip order to make min priority queue
}
bool operator==(const Grid_Pos& lhs, const Grid_Pos& rhs){
    return lhs.pos.first == rhs.pos.first && lhs.pos.second == rhs.pos.second;
}
bool operator!=(const Grid_Pos& lhs, const Grid_Pos& rhs){
    return lhs.pos.first != rhs.pos.first || lhs.pos.second != rhs.pos.second;
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
    Grid_Pos position = Grid_Pos();
    Grid_Pos next_position = {make_pair(-1,-1), -1};

    while( cin >> TILE_N ){
        for( int i = 0; i < TILE_N; i++ ){
            cin >> TILE_NAME;
            cin >> TILE_COST;
            tiles.insert(pair<char,int>(TILE_NAME, TILE_COST));
        }

        cin >> MAP_ROWS;
        cin >> MAP_COLUMNS;

        // Initial Values
        map<pair<int,int>, int> dist;
        map<pair<int,int>, pair<int,int>> prev;

        char val;
        for( int i = 0; i < MAP_ROWS; i++ ){
            vector<char> temp;
            for( int j = 0; j < MAP_COLUMNS; j++ ){
                cin >> val;
                temp.push_back(val);
                position = {make_pair(i,j), tiles[val]};
                dist.insert(make_pair(position.pos, INT_MAX));       
                //prev.insert(make_pair(position.pos, next_position.pos));
            }
            grid.push_back(temp);
        }
        cin >> RUNNER_START_ROW;
        cin >> RUNNER_START_COL;
        cin >> RUNNER_END_ROW;
        cin >> RUNNER_END_COL;

        priority_queue<Grid_Pos, vector<Grid_Pos> > frontier;
        set<Grid_Pos> marked;
        vector<Grid_Pos> visited;
        char name; int cost;
        int target_row = RUNNER_END_ROW;
        int target_col = RUNNER_END_COL;
        
        name = grid[RUNNER_START_ROW][RUNNER_START_COL];
        cost = tiles[name];
        Grid_Pos start_position = {make_pair(RUNNER_START_ROW, RUNNER_START_COL), cost};

 
        int total_cost = 0;
        name = grid[target_row][target_col];
        cost = tiles[name];
        position = {make_pair(target_row, target_col), cost};

        dist[position.pos] = 0;
        prev[position.pos] = make_pair(-1,-1);
        while( visited.empty() || visited[visited.size()-1] != start_position ){
            //cout << target_row << " " << target_col << endl;
            marked.insert(position);
            visited.push_back(position);
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
                        cout << name << endl;
                        cost = tiles[name];
                        next_position = {make_pair(i, j), cost};
                        cout << "Current distance: " << dist[next_position.pos] << endl;
                        cout << "Possible distance: " << dist[position.pos] + cost << endl;
                        if( dist[position.pos] + cost < dist[next_position.pos] ){
                            dist[next_position.pos] = dist[position.pos] + cost;
                            //cout << dist[position] + cost << endl;
                            prev[next_position.pos] = position.pos;
                            //cout << next_position.row << " " << next_position.col << " " << position.row << " " << position.col << endl;
                            //position = next_position;
                        }
                        frontier.push({make_pair(i,j), dist[next_position.pos]});          
                    }
                }   
            }
            while( !frontier.empty() && marked.find(frontier.top()) != marked.end() ){
                frontier.pop();
            }
            //cout << frontier.top().row << " " << frontier.top().col << endl;
            target_row = frontier.top().pos.first;
            target_col = frontier.top().pos.second;
            //total_cost += frontier.top().cost;
            name = grid[target_row][target_col];
            cout << "CHosen lowest: " << name << endl;
            cost = tiles[name];
            position = {make_pair(target_row, target_col), cost};
            frontier.pop();
            //bool myVal = visited[visited.size()-1] != start_position; 
            //cout << myVal << endl;
            //cout << target_row << " " << target_col << endl;
        }
    
        int temp_row = RUNNER_START_ROW;
        int temp_col = RUNNER_START_COL;
        total_cost = dist[make_pair(temp_row,temp_col)];
        cout << total_cost << endl;
        //cout << dist[position] << endl;
        while( temp_row != -1 && temp_col != -1 ){
            cout << temp_row << " " << temp_col << endl;
            name = grid[temp_row][temp_col];
            position = {make_pair(temp_row, temp_col), tiles[name]};
            temp_row = prev[position.pos].first;
            temp_col = prev[position.pos].second;
        }
   }
    return 0;
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
