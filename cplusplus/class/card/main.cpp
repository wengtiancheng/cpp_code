//
// Created by wtc on 2024/12/19.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int find(int score, const vector<int>& cards, int size) {
    int ptr = -1;
    for(int i = 0; i < size; i++) {
        if(cards[i] == score) {
            ptr = i;
            break;
        }
    }
    if(ptr == -1) {
        return -1;
    }
    int count = 1;
    bool left_bool = false;
    bool right_bool = false;
    for(int i = ptr + 1; i < size; i++) {
        if(!right_bool) {
            right_bool = true;
            continue;
        }
        if(cards[i] > score) {
            right_bool = true;
            continue;
        }

        if(cards[i] <= score) {
            right_bool = false;
            count++;
            continue;
        }
    }
    for(int i = ptr - 1; i >= 0; i--) {
        if(!left_bool) {
            left_bool = true;
            continue;
        }
        if(cards[i] > score) {
            left_bool = true;
            continue;
        }

        if(cards[i] <= score) {
            left_bool = false;
            count++;
            continue;
        }
    }
    return count;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> cards(n, 0);

    for(int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        cards[i] = tmp;
    }
    vector<int> tmp = cards;
    sort(tmp.begin(), tmp.end());
    int left = 0;
    int right = n - 1;
    int mid = 0;
    int result = 0;
    while(left <= right) {
        mid = (left + right) / 2;
        int num = tmp[mid];
        if(find(num, cards, n) >= k) {
            result = num;
            right = mid - 1;
        }else if(find(num, cards, n) < k) {
            left = mid + 1;
        }
    }
    cout << result;
    return 0;
}