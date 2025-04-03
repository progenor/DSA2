#include <bits/stdc++.h>

using namespace std;

ifstream file("../in.txt");

void readArray(int *a, int n){
    if(n >= 0){
        readArray(a, n-1); 
        file>>a[n];
    }
}

void printArray(int *a, int n){
    if(n >= 0) {
        printArray(a, n-1);
        cout<<a[n]<<" ";
    }
}

int sumArrayTwoDigits(int *a, int n){
    if(n >= 0){
        if(a[n]/10 % 10 != 0 && a[n]/100 % 10 == 0){
            return a[n] + sumArrayTwoDigits(a, n-1);
        }
        return 0 + sumArrayTwoDigits(a, n-1);
    }
    else return 0;
}

int szamjegy_elofordulas(int szam, int szamjegy){
    if(szam == 0) return 0;
    if(szam%10 == szamjegy) return 1 + szamjegy_elofordulas(szam/10, szamjegy);
    else return szamjegy_elofordulas(szam/10, szamjegy);
}

bool is_binary(int n){
    if(n == 0) return true;
    if((n%10 == 0) || (n%10 == 1)) return is_binary(n/10);
    else return false;
}

int main(){
    int n;
    file>> n;
    int a[n];
    readArray(a, n-1);
    cout<< sumArrayTwoDigits(a, n-1);

    cout<< szamjegy_elofordulas(123123123, 1) << endl;
    cout << is_binary(1010101011) << endl;
    cout << is_binary(1012101) << endl;

    // printArray(a, n-1);
}