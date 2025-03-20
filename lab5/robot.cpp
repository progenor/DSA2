#include <bits/stdc++.h>
using namespace std;

// Define directions: up, right, down, left
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

vector<vector<int>> readFile(int& n, int& m) {
    vector<vector<int>> place;
    // cin >> n >> m;
    // place.resize(n, vector<int>(m));
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < m; j++) {
    //         cin >> place[i][j];
    //     }
    // }
    ifstream file("../hegy.txt");
    file >> n >> m;
    place.resize(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            file >> place[i][j];
        }
    }
    return place;
}

void printPlace(vector<vector<int>> place) {
    for(auto i = 0; i < place.size(); i++) {
        for(auto j = 0; j < place[i].size(); j++) {
            cout << place[i][j] << " ";
        }
        cout << endl;
    }
}

void findAllPaths(vector<vector<int>>& lab, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    unordered_map<int, int> slipperinessCount;
    
    vector<pair<int, int>> path;
    
    vector<vector<pair<int, int>>> validPaths;
    
    function<void(int, int)> dfs = [&](int x, int y) {
        path.push_back({x, y});
        
        visited[x][y] = true;
        
        slipperinessCount[lab[x][y]]++;
        
        if (x == n-1 && y == m-1) {
            validPaths.push_back(path);
        } else {
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && 
                    lab[nx][ny] >= lab[x][y] && slipperinessCount[lab[nx][ny]] < 2) {
                    dfs(nx, ny);
                }
            }
        }
        
        visited[x][y] = false;
        slipperinessCount[lab[x][y]]--;
        path.pop_back();
    };
    
    dfs(0, 0);
    
    if (validPaths.empty()) {
        cout << "nincs megoldas" << endl;
    } else {
        cout<< "ossz: " << validPaths.size() << endl;
        for (int pathIdx = 0; pathIdx < validPaths.size(); pathIdx++) {
            cout << pathIdx+1 << ":" << endl;
            
            vector<vector<string>> grid(n, vector<string>(m, "-"));
            
            for (int step = 0; step < validPaths[pathIdx].size(); step++) {
                int x = validPaths[pathIdx][step].first;
                int y = validPaths[pathIdx][step].second;
                grid[x][y] = to_string(step + 1);
            }
            
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cout << grid[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
}

int main() {
    int n, m;
    vector<vector<int>> lab = readFile(n, m);
    
    findAllPaths(lab, n, m);
    
    return 0;
}