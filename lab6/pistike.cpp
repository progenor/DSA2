#include <bits/stdc++.h>

using namespace std;

typedef struct {
    int score;
    float time;
    int pos;
} Vizsga;

int from, to;




Vizsga* readFromFile(int &n){
    ifstream file("../in.txt");
    if(!file.is_open()) perror("Error opening file");
    file >> n;
    Vizsga* vizsgak = new Vizsga[n];

    for(int i = 0; i < n; i++){
        file >> vizsgak[i].score >> vizsgak[i].time;
        vizsgak[i].pos = i;
    }

    file >> from >> to;

    file.close();

    return vizsgak;
}

vector<int> getMaxScoreEfficient(Vizsga* vizsgak, int n) {
    Vizsga* sortedVizsgak = new Vizsga[n];
    for (int i = 0; i < n; i++) {
        sortedVizsgak[i] = vizsgak[i];
    }
    
    sort(sortedVizsgak, sortedVizsgak + n, 
         [](const Vizsga& a, const Vizsga& b) { 
             return (float)a.score / a.time > (float)b.score / b.time; 
         });
    
    vector<int> selectedExams;
    float timeUsed = 0;
    float availableTime = to - from;
    int totalScore = 0;
    
    for (int i = 0; i < n; i++) {
        if (timeUsed + sortedVizsgak[i].time <= availableTime) {
            selectedExams.push_back(sortedVizsgak[i].pos);
            timeUsed += sortedVizsgak[i].time;
            totalScore += sortedVizsgak[i].score;
        }
    }
    
    for(auto i : selectedExams){
        cout << i << " " ;
    }
    cout<< endl;

    delete[] sortedVizsgak;
    return selectedExams;
}

void findAllCombBack(Vizsga* vizsgak, int n, int from, int to) {
    float availableTime = to - from;
    vector<int> currentSelection;
    
    function<void(int, float)> backtrack = [&](int index, float timeUsed) {
        if (index == n) {
            if (!currentSelection.empty()) {
                for (int idx : currentSelection) {
                    cout << idx << " ";
                }
                cout << "| time: " << timeUsed << "/" << availableTime << endl;
            }
            return;
        }
        
        backtrack(index + 1, timeUsed);
        
        if (timeUsed + vizsgak[index].time <= availableTime) {
            currentSelection.push_back(index);
            backtrack(index + 1, timeUsed + vizsgak[index].time);
            currentSelection.pop_back(); 
        }
    };
    
    backtrack(0, 0);
}




vector<int> getMaxExams(Vizsga* vizsgak, int n, int from, int to) {
    Vizsga* sortedVizsgak = new Vizsga[n];
    for (int i = 0; i < n; i++) {
        sortedVizsgak[i] = vizsgak[i];
    }
    
    sort(sortedVizsgak, sortedVizsgak + n, 
         [](const Vizsga& a, const Vizsga& b) { return a.time < b.time; });
    
    vector<int> selectedExams;
    float timeUsed = 0;
    float availableTime = to - from;
    
    for (int i = 0; i < n; i++) {
        if (timeUsed + sortedVizsgak[i].time <= availableTime) {
            selectedExams.push_back(sortedVizsgak[i].pos);
            timeUsed += sortedVizsgak[i].time;
        }
    }
    
    delete[] sortedVizsgak;
    return selectedExams;
}

void getMax(Vizsga * vizsgak, int n){
    vector<int> maxExams = getMaxExams(vizsgak, n, from, to);
    
    cout << "exams ";
    for (int idx : maxExams) {
        cout << idx << " ";
    }
    cout << endl;
    
    float totalTime = 0;
    for (int idx : maxExams) {
        totalTime += vizsgak[idx].time;
    }
    cout << "total : " << totalTime << "from " << (to-from) << endl;
    
}



int main() {
    int n = 0;
    Vizsga* vizsgak = readFromFile(n);
    // getMax(vizsgak, n);
    // getMaxScoreEfficient(vizsgak, n);
    findAllCombBack(vizsgak, n, from, to);
    

    
    delete[] vizsgak;
    return 0;
}