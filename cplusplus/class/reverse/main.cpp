//
// Created by wtc on 2024/12/23.
//
#include <iostream>
#include <stdexcept>
using namespace std;

int main() {
    int n;
    cin >> n;
    string str = to_string(n);
    int len = str.size();
    string res = "";
    if(str[0] == '-') {
        res += "-";
        for(int i = len - 1; i >= 1; i--) {
            res += str[i];
        }
    }else {
        for(int i = len - 1; i >= 0; i--) {
            res += str[i];
        }
    }

    try {
        int num = std::stoi(res);
        cout << num << endl;
    }catch (const std::out_of_range& e) {
        cout << -1 << endl;
    }
    return 0;
}