#include <bits/stdc++.h>
using namespace std;

struct Item {
    string name;
    int hardness;
};

void merge(vector<Item>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Item> L(n1);
    vector<Item> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].hardness >= R[j].hardness) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Item>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    vector<Item> items = {
        {"OR", 10},
        {"Numerikus", 8},
        {"haskel", 7},
        {"dsa2", 5}
    };

    mergeSort(items, 0, items.size() - 1);

    cout << "Sorted items by hardness (high to low):" << endl;
    for (const auto& item : items) {
        cout << item.name << " with hardness " << item.hardness << endl;
    }

    return 0;
}