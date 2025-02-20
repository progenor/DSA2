#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

vector<long long> fiboC(50, -1);

long long fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    if (fiboC[n] != -1) {
        return fiboC[n];
    }
    fiboC[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return fiboC[n];
}

int main() {
    cout << fibonacci(49) << endl;
    return 0;
}