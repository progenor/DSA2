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


int findMaxPathLength(vector<vector<int>>& place, int n, int m) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int maxPathLength = 0;

    vector<vector<string>> maxPath(n, vector<string>(m, " "));
    
    function<void(int, int, int)> dfs = [&](int x, int y, int pathLength) {
        if (x == n-1 && y == m-1) {
            maxPathLength = max(maxPathLength, pathLength);

        int cnt=1;
        for(auto i = 0; i < n; i++) {
            for(auto j = 0; j < m; j++) {
                if(visited[i][j]) maxPath.at(i).at(j) = " " + to_string(cnt++) + " ";
                else maxPath.at(i).at(j) = " - ";
            }
            cout << endl;
        }


            return;
        }
        
        visited[x][y] = true;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && place[nx][ny] >= place[x][y]) {
                dfs(nx, ny, pathLength + 1);
            }
        }
        
        visited[x][y] = false;
    };
    
    dfs(0, 0, 1);

   
    for(auto i = 0; i < n; i++) {
        for(auto j = 0; j < m; j++) {
            cout << maxPath.at(i).at(j);
        }
        cout << endl;
    }
    return maxPathLength;
}

int main() {
    int n, m;
    vector<vector<int>> place = readFile(n, m);
    
    int maxPathLength = findMaxPathLength(place, n, m);
    
    if (maxPathLength > 0) {
        cout << maxPathLength << endl;
    } else {
        cout << "nincs megoldas" << endl;
    }
    
    return 0;
}