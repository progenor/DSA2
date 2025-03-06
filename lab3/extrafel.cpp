#include <bits/stdc++.h>

using namespace std;

typedef struct Subject {
    int dif;  
    string name;
} Subject;

// Functions declarations
void mergeSort(vector<Subject>& subjects, int left, int right);
vector<Subject> readFileContent(string filename);
void printSubjects(const vector<Subject>& subjects);
void merge(vector<Subject>& subjects, int left, int mid, int right);
void binarySearch(const vector<Subject>& subjects, int what);




int main() {

    vector<Subject> subjects = readFileContent("../tantargyak.txt");
    
    printSubjects(subjects);
    
    if (!subjects.empty()) {
        mergeSort(subjects, 0, subjects.size() - 1);
    }
    cout<<endl;
    
    printSubjects(subjects);
    
    cout << "\nBinary search for 8:" << endl;
    binarySearch(subjects, 8);

    return 0;
}


void merge(vector<Subject>& subjects, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<Subject> L(n1), R(n2);
    
    for(int i = 0; i < n1; i++)
        L[i] = subjects[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = subjects[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while(i < n1 && j < n2) {
        if(L[i].dif <= R[j].dif) {
            subjects[k] = L[i];
            i++;
        } else {
            subjects[k] = R[j];
            j++;
        }
        k++;
    }
    
    while(i < n1) {
        subjects[k] = L[i];
        i++;
        k++;
    }
    
    while(j < n2) {
        subjects[k] = R[j];
        j++;
        k++;
    }
}

void binarySearchRecursive(const vector<Subject>& subjects, int what, int left, int right) {
    if (left > right) {
        cout << "Not found: " << what << endl;
        return;
    }
    
    int mid = left + (right - left) / 2;
    
    if (subjects[mid].dif == what) {
        cout << "Found: " << subjects[mid].dif << " " << subjects[mid].name << endl;
        return;
    }
    
    if (subjects[mid].dif > what)
        binarySearchRecursive(subjects, what, left, mid - 1);
    else
        binarySearchRecursive(subjects, what, mid + 1, right);
}

void binarySearch(const vector<Subject>& subjects, int what) {
    binarySearchRecursive(subjects, what, 0, subjects.size() - 1);
}

void mergeSort(vector<Subject>& subjects, int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(subjects, left, mid);
        mergeSort(subjects, mid + 1, right);
        
        merge(subjects, left, mid, right);
    }
}

void printSubjects(const vector<Subject>& subjects) {
    for(const auto& subject : subjects) {
        cout << subject.dif << " " << subject.name << endl;
    }
}

vector<Subject> readFileContent(string filename){
    vector<Subject> subjects;
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file: " << filename << endl;
        return subjects;
    }
    
    string line;
    while(getline(file, line)) {
        Subject subject;
        stringstream ss(line);
        
        ss >> subject.dif;
        getline(ss >> ws, subject.name); 
        
        subjects.push_back(subject);
    }
    
    file.close();
    return subjects;
}