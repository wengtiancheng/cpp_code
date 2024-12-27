#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 字母频率统计
map<char, int> letterFreq;

void addWord(const string& word) {
    for (char c : word) {
        letterFreq[c]++;
    }
}

void queryMaxFrequency() {
    int maxFreq = 0;
    vector<char> result;

    // 找到频率最高的字母
    for (auto& pair : letterFreq) {
        if (pair.second > maxFreq) {
            maxFreq = pair.second;
            result.clear();
            result.push_back(pair.first);
        } else if (pair.second == maxFreq) {
            result.push_back(pair.first);
        }
    }

    // 按字母顺序排序
    sort(result.begin(), result.end());

    // 输出结果
    for (char c : result) {
        cout << c;
    }
    cout << endl;
}

int main() {
    int q;
    cin >> q;

    string operation, word;

    // 处理q次操作
    for (int i = 0; i < q; i++) {
        cin >> operation;
        if (operation == "add") {
            cin >> word;
            addWord(word);
        } else if (operation == "query") {
            queryMaxFrequency();
        }
    }

    return 0;
}
