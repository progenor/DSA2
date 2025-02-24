#include <bits/stdc++.h>
using namespace std;

vector<int> res, rnk, pers, ranked;

void calculateRank(int i, int y) {
    if (i == ranked.size()) return;
    if (i > 0 && ranked[i - 1] > ranked[i]) y++;
    rnk.push_back(y);
    calculateRank(i + 1, y);
}

void findPlayerRank(int i, int j) {
    if (i == pers.size()) return;
    while (j >= 0 && pers[i] >= ranked[j]) j--;
    res.push_back(j == -1 ? 1 : rnk[j] + 1);
    findPlayerRank(i + 1, j);
}

int main() {
    int n, r, x;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x;
        ranked.push_back(x);
    }
    cin >> r;
    for (int i = 0; i < r; i++) {
        cin >> x;
        pers.push_back(x);
    }

    calculateRank(0, 1);
    findPlayerRank(0, ranked.size() - 1);

    for (int rank : res) {
        cout << rank << endl;
    }

    return 0;
}