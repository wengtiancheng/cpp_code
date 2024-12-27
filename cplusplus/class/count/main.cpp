//
// Created by wtc on 2024/12/23.
//
#include <iostream>
#include <sstream>
#include <string>
using namespace std;


int main() {
    string line;
    int wordCount = 0;
    int charCount = 0;
    int lineCount = 0;

    while(getline(cin, line)) {
        lineCount++;
        charCount += line.size();
        charCount++;
        stringstream ss(line);
        string word;
        while(ss >> word) {
            wordCount++;


        }
    }
    cout << charCount << " " << wordCount << " " << lineCount;


    return 0;
}