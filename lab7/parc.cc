#include <bits/stdc++.h>

using namespace std;

int papir[] = {200, 100, 50, 20, 10, 5, 1};
int bani[]  = {50, 10, 5 ,1};
int n = sizeof(papir)/sizeof(papir[0]);
int m = sizeof(bani)/sizeof(bani[0]);

int main() {
    int  osszeg = 250 - 236.18;
    float banik = 250 - 236.18;
    cout << "Osszeg: " << osszeg << endl;
    vector<int> visszajaro;
    for(int i = 0; i < n; i++){
        while(osszeg >= papir[i]){
            osszeg -= papir[i];
            visszajaro.push_back(papir[i]);
        }
    }
    // for(int i = 0; i < m; i++){
    //     while(osszeg >= bani[i]){
    //         osszeg -= bani[i];
    //         visszajaro.push_back(bani[i]);
    //     }
    // }
    cout << "Visszajaro: ";
    for(auto i : visszajaro){
        cout << i << " ";
    }
}
