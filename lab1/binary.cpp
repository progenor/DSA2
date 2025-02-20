#include <stdlib.h>
#include <iostream>
#include <errno.h>
#include <vector>

using namespace std;

void binarySearch(const vector<int>& arr, int left, int right, int target) {
    if (left <= right) {
        int mid = (left+right) / 2;

        if (arr[mid] == target){
            cout<<mid<<" ";
            binarySearch(arr, left, mid - 1, target);
            binarySearch(arr, mid + 1, right, target);
        } else if (arr[mid] > target) {
            binarySearch(arr, left, mid - 1, target);
        } else {
            binarySearch(arr, mid + 1, right, target);
        } 
    }

}




int main(){
    vector<int> arr = {1, 2, 3, 4, 5,5,5,5,5, 6, 7, 8, 9};
    binarySearch(arr, 0, arr.size()-1, 5);
    // cout<<"Position: " << pos<<endl;
    // cout<<"Number on position: "<< arr[pos]<<endl; 
}