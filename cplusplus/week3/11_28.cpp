#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Store {
private:
    unordered_map<string, int> inventory;

public:
    Store() {
        inventory["Chicken"] = 0;
        inventory["Lettuce"] = 0;
        inventory["Tomato"] = 0;
        inventory["Cheese"] = 0;
        inventory["Onion"] = 0;
        inventory["Sauce"] = 0;
    }

    void add_stock(string type, int num) {
        inventory[type] += num;
        cout << "Stocked " << type << " with " << num << " units" << endl;
    }

    void order(const string& id, const vector<pair<string, int>>& list) {
        unordered_map<string, int> missing;
        for (auto& item : list) {
            if (inventory[item.first] < item.second) {
                missing[item.first] = item.second - inventory[item.first];
            }
        }

        if (missing.empty()) {
            for (auto& item : list) {
                inventory[item.first] -= item.second;
            }
            cout << "Order " << id << " completed" << endl;
        } else {
            cout << "Order " << id << " failed: missing";
            bool first = true;
            for (auto& item : list) {
                if (missing.find(item.first) != missing.end()) {
                    if (!first) cout << ", ";
                    cout << item.first << " " << missing[item.first];
                    first = false;
                }
            }
            cout << endl;
        }
    }

    void inventory_status(){
        cout << "=== Inventory ===" << endl;
        cout << "Chicken: " << inventory.at("Chicken") << endl;
        cout << "Lettuce: " << inventory.at("Lettuce") << endl;
        cout << "Tomato: " << inventory.at("Tomato") << endl;
        cout << "Cheese: " << inventory.at("Cheese") << endl;
        cout << "Onion: " << inventory.at("Onion") << endl;
        cout << "Sauce: " << inventory.at("Sauce") << endl;
        cout << "=================" << endl;
    }
};

int main() {
    Store store;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string command;
        cin >> command;
        if (command == "Stock") {
            string type;
            int num;
            cin >> type >> num;
            store.add_stock(type, num);
        } else if (command == "Order") {
            string id;
            cin >> id;
            vector<pair<string, int>> list;
            string ingredient;
            int quantity;
            while (cin >> ingredient >> quantity) {
                list.emplace_back(ingredient, quantity);
                if (cin.peek() == '\n') break;
            }
            store.order(id, list);
        } else if (command == "Inventory") {
            store.inventory_status();
        }
    }
    return 0;
}