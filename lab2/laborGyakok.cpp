#include <iostream>
using namespace std;

/**
* Checks if the elements in the array a, from index f to l
(inclusive), alternate in parity (odd and even).
*
* @param a The array of natural numbers.
* @param f The first index of the segment to check.
* @param l The last index of the segment to check.
* @return 1 if the numbers alternate in parity, 0 otherwise.
*/
int AlternDivImp(int a[], int f, int l) {
    if (f >= l) {
        return 1;
    }
    if ((a[f] % 2) == (a[f + 1] % 2)) {
        return 0;
    }
    return AlternDivImp(a, f + 1, l);
}

int main() {
    int a[] = { 2, 3, 4, 6, 7, 8 };
    cout << AlternDivImp(a, 0, 5) << endl;
}