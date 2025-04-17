#ifndef LABOR9_FUNCTION_H
#define LABOR9_FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

typedef struct {
    int colors = 0;
    int father = -1;
    int distance = __INT_MAX__;
    vector<int> neighbors;
} POINT;

vector<POINT> readFromFile(char filename[201]) {
    ifstream fin(filename);
    int nrPoints;
    fin >> nrPoints;
    int nrEdges;
    fin >> nrPoints >> nrEdges;
    
    cout << nrEdges << " " << nrPoints;
    
    vector<POINT> aPoints(nrPoints);
    for (int i = 0; i < nrEdges; i++) {
        int from, to;
        fin >> from >> to;
        cout << from << " " << to;
        aPoints.at(from - 1).neighbors.push_back(to);
        aPoints.at(to - 1).neighbors.push_back(from);
    }
    
    return aPoints;
}

void printVector(vector<POINT>& aPoints) {
    for (int i = 0; i < aPoints.size(); i++) {
        cout << "Index: " << i + 1 << "\n";
        cout << "Color: " << aPoints.at(i).colors << "\n";
        cout << "Father: " << aPoints.at(i).father << "\n";
        cout << "Neighbors: ";
        for (int j = 0; j < aPoints.at(i).neighbors.size(); j++) {
            cout << aPoints.at(i).neighbors.at(j) << " ";
        }
        cout << "\n";
    }
}

void printVectorInt(vector<int>& vector) {
    for (int i = 0; i < vector.size(); i++) {
        cout << vector.at(i) << " ";
    }
    cout << "\n";
}

#endif //LABOR9_FUNCTION_H