#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> str;

void common_sort() {
    sort(str.begin, str.end(), [](const string& a, const string& b) {
        return a < b;
    });
}

void num_sort() {

}

void reverse_sort() {

}

int main() {
    int n;
    std::cin >> n;
    std::cin >> std::ws;// try to comment out the line
    for(int i = 0; i < n; i++){
        std::string s;
        std::getline(std::cin, s);
        str.push_back(s);
    }
    int c;
    cin >> c;
    for(int i = 0; i < c; i++){
        char command;
        cin >> command;
        if(command = '-'){

        }else if(command == 'n'){

        }else if(command == 'r'){

        }else if(command == 'i'){

        }else if(command == 'd'){

        }else{
            cout << "Invalid command" << endl;
        }

    }
    return 0;

}