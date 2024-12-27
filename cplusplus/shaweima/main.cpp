//
// Created by wtc on 2024/12/24.
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
using namespace std;


class Store {
public:
    unordered_map<string, int> inventory;
    Store() {
        inventory["Chicken"] = 0;
        inventory["Lettuce"] = 0;
        inventory["Tomato"] = 0;
        inventory["Cheese"] = 0;
        inventory["Onion"] = 0;
        inventory["Source"] = 0;
    }

    void stock(const string& name, const int num) {
        inventory[name] += num;
        cout << "Stocked " << name << " with " << num << " units" << endl;
    }

    void order(string id, vector<pair<string, int>> food) {
        vector<pair<string, int>> miss = {};
        bool enough = true;
        for(const auto& it : food) {
            if(inventory[it.first] - it.second < 0) {
                enough = false;
                miss.emplace_back(it.first, it.second - inventory[it.first]);
            }
        }
        if(enough) {
            for(const auto& it : food) {
                inventory[it.first] -= it.second;
            }
            cout << "Order " << id << " completed" << endl;
        }else {
            cout << "Order " << id << " failed: missing";
            bool first = true;
            for(int i = 0; i < miss.size(); i++) {
                cout << miss[i].first << " "  << miss[i].second;
                if(i != miss.size() - 1) {
                    cout << ",";
                }
            }
            cout << endl;

        }
    }

    void query() {
        cout << "=== Inventory ===" << endl;
        cout << "Chicken: " << inventory["Chicken"] << endl;
        cout << "Lettuce: " << inventory["Lettuce"] << endl;
        cout << "Tomato: " << inventory["Tomato"] << endl;
        cout << "Cheese: " << inventory["Cheese"] << endl;
        cout << "Onion: " << inventory["Onion"] << endl;
        cout << "Sauce: " << inventory["Sauce"] << endl;
        cout << "=================" << endl;
    }

};

int main() {
    Store store = Store();
    int n;
    cin >> n;
    cin.get();
    for(int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);
        string command;
        ss >> command;
        if(command == "Stock") {
            string name;
            int num;
            ss >> name >> num;
            store.stock(name, num);
        }else if(command == "Order") {
            string id;
            ss >> id;
            vector<pair<string, int>> need;
            string name;
            int count;
            while(ss >> name >> count) {
                need.emplace_back(name, count);

            }
            store.order(id, need);
        }else if(command == "Inventory") {
            store.query();
        }else {
            cout << command;
            cout << "Invalid command" << endl;
        }
    }
    return 0;

    //emplace_back和push_back的区别
    //sth<vector>.end()可不可以使用
    //读取一行未知单词数目的指令
}