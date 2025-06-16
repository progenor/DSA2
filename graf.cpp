#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
using namespace std;

// Current Date and Time: 2025-05-14 19:52:53

class Graph {
private:
    int numNodes;
    bool isDirected;
    bool isWeighted;
    vector<vector<pair<int, int>>> adjList; // Pair: (neighbor, weight)

public:
    Graph(int n, bool directed = false, bool weighted = false) 
        : numNodes(n), isDirected(directed), isWeighted(weighted) {
        adjList.resize(n + 1);  // +1 for 1-indexed nodes
    }
    
    void addEdge(int u, int v, int weight = 1) {
        adjList[u].push_back({v, weight});
        if (!isDirected) {
            adjList[v].push_back({u, weight});
        }
    }
    
    void readFromInput() {
        int m;
        cout << "Enter number of edges: ";
        cin >> m;
        
        if (isWeighted) {
            cout << "Enter " << m << " edges (u v weight format):" << endl;
            for (int i = 0; i < m; i++) {
                int u, v, weight;
                cin >> u >> v >> weight;
                addEdge(u, v, weight);
            }
        } else {
            cout << "Enter " << m << " edges (u v format):" << endl;
            for (int i = 0; i < m; i++) {
                int u, v;
                cin >> u >> v;
                addEdge(u, v);
            }
        }
    }
    
    void printGraph() const {
        cout << "Graph Adjacency List:" << endl;
        for (int i = 1; i <= numNodes; i++) {
            cout << "Node " << i << ": ";
            for (const auto& edge : adjList[i]) {
                int neighbor = edge.first;
                int weight = edge.second;
                
                if (isWeighted) {
                    cout << neighbor << "(" << weight << ") ";
                } else {
                    cout << neighbor << " ";
                }
            }
            cout << endl;
        }
    }
    
    // BFS traversal
    vector<int> bfs(int start) {
        vector<bool> visited(numNodes + 1, false);
        vector<int> traversal;
        queue<int> q;
        
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            traversal.push_back(u);
            
            for (const auto& edge : adjList[u]) {
                int v = edge.first;
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        
        return traversal;
    }
    
    // DFS traversal
    vector<int> dfs(int start) {
        vector<bool> visited(numNodes + 1, false);
        vector<int> traversal;
        dfsUtil(start, visited, traversal);
        return traversal;
    }
    
    // Search for a node - returns path from start to target if found
    vector<int> findPath(int start, int target) {
        vector<bool> visited(numNodes + 1, false);
        vector<int> parent(numNodes + 1, -1);
        queue<int> q;
        
        q.push(start);
        visited[start] = true;
        
        bool found = false;
        while (!q.empty() && !found) {
            int u = q.front();
            q.pop();
            
            if (u == target) {
                found = true;
                break;
            }
            
            for (const auto& edge : adjList[u]) {
                int v = edge.first;
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }
        
        // If target was not found
        if (parent[target] == -1 && target != start) {
            return {};
        }
        
        // Reconstruct path
        vector<int> path;
        for (int at = target; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    
    // Dijkstra's algorithm for shortest path in weighted graphs
    vector<int> shortestPath(int start, int target) {
        if (!isWeighted) {
            return findPath(start, target); // Use BFS for unweighted
        }
        
        vector<int> dist(numNodes + 1, numeric_limits<int>::max());
        vector<int> parent(numNodes + 1, -1);
        vector<bool> visited(numNodes + 1, false);
        
        dist[start] = 0;
        
        // Priority queue: pair<distance, node>
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            if (u == target) break; // Found target
            
            for (const auto& edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        // If target is unreachable
        if (dist[target] == numeric_limits<int>::max()) {
            return {};
        }
        
        // Reconstruct path
        vector<int> path;
        for (int at = target; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }
    
    // Check if a path exists between two nodes
    bool hasPath(int start, int target) {
        return !findPath(start, target).empty();
    }
    
    // Simple DisjointSet class for cycle detection
    class DisjointSet {
    private:
        vector<int> parent;
        
    public:
        DisjointSet(int n) {
            parent.resize(n + 1);
            for (int i = 1; i <= n; i++)
                parent[i] = i;
        }
        
        // Find root with path compression
        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }
        
        // Union by assigning one root as parent of another
        void unite(int x, int y) {
            parent[find(x)] = find(y);
        }
    };
    
    // Kruskal's algorithm - Add this as a method to your Graph class
    void kruskalMST() {
        // 1. Create a vector of all edges
        vector<tuple<int, int, int>> edges; // (weight, u, v)
        for (int u = 1; u <= numNodes; u++) {
            for (const auto& edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (u < v) // Avoid duplicates in undirected graph
                    edges.push_back({weight, u, v});
            }
        }
        
        // 2. Sort edges by weight
        sort(edges.begin(), edges.end());
        
        // 3. Initialize result
        vector<tuple<int, int, int>> result;
        DisjointSet ds(numNodes);
        int totalWeight = 0;
        
        // 4. Process edges in order of increasing weight
        cout << "Edges in MST:" << endl;
        for (const auto& edge : edges) {
            int weight = get<0>(edge);
            int u = get<1>(edge);
            int v = get<2>(edge);
            
            // If including this edge doesn't create a cycle
            if (ds.find(u) != ds.find(v)) {
                // Add to MST
                result.push_back(edge);
                totalWeight += weight;
                ds.unite(u, v);
                
                cout << u << " -- " << v << " (weight: " << weight << ")" << endl;
                
                // MST has n-1 edges
                if (result.size() == numNodes - 1)
                    break;
            }
        }
        
        cout << "Total MST weight: " << totalWeight << endl;
    }
    
private:
    // Recursive utility function for DFS
    void dfsUtil(int node, vector<bool>& visited, vector<int>& traversal) {
        visited[node] = true;
        traversal.push_back(node);
        
        for (const auto& edge : adjList[node]) {
            int neighbor = edge.first;
            if (!visited[neighbor]) {
                dfsUtil(neighbor, visited, traversal);
            }
        }
    }
};

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;
    
    // Create a weighted graph
    Graph g(n, false, true);
    g.readFromInput();
    g.printGraph();
    
    int startNode = 1;
    cout << "BFS starting from node " << startNode << ": ";
    vector<int> bfsOrder = g.bfs(startNode);
    for (int node : bfsOrder) {
        cout << node << " ";
    }
    cout << endl;
    
    cout << "DFS starting from node " << startNode << ": ";
    vector<int> dfsOrder = g.dfs(startNode);
    for (int node : dfsOrder) {
        cout << node << " ";
    }
    cout << endl;
    
    // Search examples
    int from = 1, to = 4;
    cout << "Finding path from " << from << " to " << to << ": ";
    vector<int> path = g.findPath(from, to);
    if (path.empty()) {
        cout << "No path exists!" << endl;
    } else {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    cout << "Finding shortest path from " << from << " to " << to << ": ";
    vector<int> shortestPath = g.shortestPath(from, to);
    if (shortestPath.empty()) {
        cout << "No path exists!" << endl;
    } else {
        for (int node : shortestPath) {
            cout << node << " ";
        }
        cout << endl;
    }
    
    // Check if a path exists
    int checkFrom = 2, checkTo = 5;
    if (g.hasPath(checkFrom, checkTo)) {
        cout << "A path exists from " << checkFrom << " to " << checkTo << endl;
    } else {
        cout << "No path exists from " << checkFrom << " to " << checkTo << endl;
    }
    
    // Kruskal's algorithm example
    g.kruskalMST();
    
    return 0;
}
