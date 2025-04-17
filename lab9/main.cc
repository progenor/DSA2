#include "Point.h"
#include <iostream>

using namespace std;

// Function to perform BFS on the graph
void BFS(vector<POINT>& graph, int startNode) {
    // Initialize all vertices
    for(int i = 0; i < graph.size(); i++) {
        graph[i].colors = 0; // white - unvisited
        graph[i].distance = __INT_MAX__;
        graph[i].father = -1;
    }
    
    // Start node (adjusting for 0-based indexing)
    int s = startNode - 1;
    graph[s].colors = 1; // gray - discovered
    graph[s].distance = 0;
    
    queue<int> q;
    q.push(s);
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        cout << "Visiting node: " << u + 1 << endl;
        
        // Process all neighbors of u
        for(int v : graph[u].neighbors) {
            // Convert from 1-based to 0-based indexing
            int v_idx = v - 1;
            
            if(graph[v_idx].colors == 0) { // If white (undiscovered)
                graph[v_idx].colors = 1; // Mark as gray (discovered)
                graph[v_idx].distance = graph[u].distance + 1;
                graph[v_idx].father = u + 1; // Store 1-based index of father
                q.push(v_idx);
            }
        }
        
        graph[u].colors = 2; // Mark as black (processed)
    }
}

int main() {
    // File path for the graph data
    char filename[201] = "../graph.txt";
    
    // Read graph from file
    cout << "Reading graph from file: " << filename << endl;
    vector<POINT> graph = readFromFile(filename);
    
    // Print the initial graph structure
    cout << "\nInitial Graph:" << endl;
    printVector(graph);
    
    // Perform BFS starting from node 1
    int startNode = 1;
    cout << "\nPerforming BFS starting from node " << startNode << ":" << endl;
    BFS(graph, startNode);
    
    // Print graph after BFS
    cout << "\nGraph after BFS:" << endl;
    printVector(graph);
    
    // Print distances from start node
    cout << "\nDistances from node " << startNode << ":" << endl;
    for(int i = 0; i < graph.size(); i++) {
        cout << "Node " << (i + 1) << ": ";
        if(graph[i].distance == __INT_MAX__) {
            cout << "Unreachable";
        } else {
            cout << graph[i].distance;
        }
        cout << endl;
    }
    
    // Print paths from start to all other nodes
    cout << "\nPaths from node " << startNode << " to all other nodes:" << endl;
    for(int i = 0; i < graph.size(); i++) {
        if(i == startNode - 1) continue; // Skip start node
        
        cout << "Path to node " << (i + 1) << ": ";
        
        if(graph[i].distance == __INT_MAX__) {
            cout << "Unreachable" << endl;
            continue;
        }
        
        // Reconstruct path
        vector<int> path;
        int current = i;
        while(current != startNode - 1) {
            path.push_back(current + 1);
            current = graph[current].father - 1;
        }
        path.push_back(startNode);
        
        // Print path in reverse order (from start to end)
        for(int j = path.size() - 1; j >= 0; j--) {
            cout << path[j];
            if(j > 0) cout << " -> ";
        }
        cout << endl;
    }
    
    return 0;
}