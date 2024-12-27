#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <regex>
using namespace std;

class Player {
public:
    string character_id;
    double base_strength;
    double base_mana;
    double base_agility;
    int level;
    string equipment;

    Player(string id) : character_id(id), level(0), base_strength(0), base_mana(0), base_agility(0), equipment("") {}

    virtual ~Player() {}

    virtual void set_attribute(const string& attribute, double value) {
        if (attribute == "base_strength") {
            base_strength = value;
        } else if (attribute == "base_mana") {
            base_mana = value;
        } else if (attribute == "base_agility") {
            base_agility = value;
        }
    }

    virtual bool equip(string type, double value) {
        if (!equipment.empty()) {
            cout << "Character " << character_id << " already has equipment" << endl;
            return false;
        }

        if (can_equip(type)) {
            equipment = type;
            apply_equip(value);
            return true;
        }

        return false;
    }

    virtual void upgrade() {
        if (level >= 5) {
            cout << "Character " << character_id << " is already at max level" << endl;
        } else {
            level++;
            increase_attributes();
        }
    }

    virtual void increase_attributes() = 0;

    virtual double get_strength() = 0;
    virtual double get_mana() = 0;
    virtual double get_agility() = 0;

    virtual double get_power() = 0;

protected:
    virtual bool can_equip(const string& type) = 0;
    virtual void apply_equip(double value) = 0;
};

class Warrior : public Player {
public:
    int weapon_strength;
    Warrior(string id) : Player(id), weapon_strength(0) {}

    void upgrade() override {
        if (level >= 5) {
            cout << "Character " << character_id << " is already at max level" << endl;
        } else {
            level++;
            increase_attributes();
        }
    }

    double get_power() override {
        return (base_strength + weapon_strength) * 1.5 + base_mana * 0.5 + base_agility * 0.8;
    }

    void increase_attributes() override {
        base_strength *= 1.1;
    }

    double get_strength() override {
        return base_strength + weapon_strength;
    }
    double get_mana() override {
        return base_mana;
    }
    double get_agility() override {
        return base_agility;
    }

protected:
    bool can_equip(const string& type) override {
        return (type == "weapon");
    }
    void apply_equip(double value) override {
        weapon_strength = value;
    }
};

class Mage : public Player {
public:
    int staff_power;
    Mage(string id) : Player(id), staff_power(0) {}

    void upgrade() override {
        if (level >= 5) {
            cout << "Character " << character_id << " is already at max level" << endl;
        } else {
            level++;
            increase_attributes();
        }
    }

    double get_power() override {
        return base_strength * 0.6 + (base_mana + 2 * staff_power) * 2.0 + base_agility * 0.7;
    }

    void increase_attributes() override {
        base_mana *= 1.2;
    }

    double get_strength() override {
        return base_strength;
    }
    double get_mana() override {
        return base_mana + 2 * staff_power;
    }
    double get_agility() override {
        return base_agility;
    }

protected:
    bool can_equip(const string& type) override {
        return (type == "staff");
    }
    void apply_equip(double value) override {
        staff_power = value;
    }
};

class Rogue : public Player {
public:
    int stealth_bonus;
    Rogue(string id) : Player(id), stealth_bonus(0) {}

    void upgrade() override {
        if (level >= 5) {
            cout << "Character " << character_id << " is already at max level" << endl;
        } else {
            level++;
            increase_attributes();
        }
    }

    double get_power() override {
        return base_strength * 0.6 + base_mana * 0.4 + (base_agility + stealth_bonus) * 1.8;
    }

    void increase_attributes() override {
        base_agility *= 1.15;
    }

    double get_strength() override {
        return base_strength;
    }
    double get_mana() override {
        return base_mana;
    }
    double get_agility() override {
        return base_agility + stealth_bonus;
    }

protected:
    bool can_equip(const string& type) override {
        return (type == "cloak");
    }
    void apply_equip(double value) override {
        stealth_bonus = value;
    }
};

class System {
public:
    map<string, Player*> players;
    map<string, vector<string>> teams;

    ~System() {
        for (auto& pair : players) {
            delete pair.second;
        }
    }

    void add(string role, string id) {
        if (role == "Warrior") {
            players[id] = new Warrior(id);
        } else if (role == "Mage") {
            players[id] = new Mage(id);
        } else if (role == "Rogue") {
            players[id] = new Rogue(id);
        }
    }

    void set(string id, string attribute, double value) {
        if (players.find(id) != players.end()) {
            players[id]->set_attribute(attribute, value);
        }
    }

    void add_team(string team_id, vector<string> player_ids) {
        teams[team_id] = player_ids;
    }

    void adjust_team(string team_id, string attribute, double value) {
        if (teams.find(team_id) != teams.end()) {
            for (auto& id : teams[team_id]) {
                if (players.find(id) != players.end()) {
                    players[id]->set_attribute(attribute, value);
                }
            }
        }
    }

    void list_normal() {
        vector<string> names;
        for (auto& pair : players) {
            names.push_back(pair.first);
        }
        // 自定义比较函数，按数字部分排序
    auto compare = [](const string& a, const string& b) {
        std::regex re("\\d+");
        std::smatch match_a, match_b;
        std::regex_search(a, match_a, re);
        std::regex_search(b, match_b, re);
        int num_a = std::stoi(match_a.str());
        int num_b = std::stoi(match_b.str());
        return num_a < num_b;
    };
        

        sort(names.begin(), names.end(), compare);

        for (auto& name : names) {
            cout << name << " ";
            cout << "strength " << players[name]->get_strength() << " ";
            cout << "mana " << players[name]->get_mana() << " ";
            cout << "agility " << players[name]->get_agility() << endl;
        }
    }

    void list_power() {
        vector<pair<string, double>> powers;
        for (auto& pair : players) {
            powers.push_back({pair.first, pair.second->get_power()});
        }

        sort(powers.begin(), powers.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
            if (a.second == b.second) {
                std::regex re("\\d+");
                std::smatch match_a, match_b;
                std::regex_search(a.first, match_a, re);
                std::regex_search(b.first, match_b, re);
                int num_a = std::stoi(match_a.str());
                int num_b = std::stoi(match_b.str());
                return num_a < num_b;
            }
            return a.second > b.second;
        });

        for (auto& p : powers) {
            cout << p.first << " ";
            cout << "strength " << players[p.first]->get_strength() << " ";
            cout << "mana " << players[p.first]->get_mana() << " ";
            cout << "agility " << players[p.first]->get_agility() << endl;
        }
    }

    void upgrade(string id) {
        if (players.find(id) != players.end()) {
            players[id]->upgrade();
        }
    }

    void equip(string id, string type, double value) {
        if (players.find(id) != players.end()) {
            players[id]->equip(type, value);
        }
    }

    void powerlist() {
        vector<pair<string, double>> powers;
        for (auto& pair : players) {
            powers.push_back({pair.first, pair.second->get_power()});
        }

        sort(powers.begin(), powers.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
            // 自定义比较函数，按数字部分排序
            std::regex re("\\d+");
            std::smatch match_a, match_b;
            std::regex_search(a.first, match_a, re);
            std::regex_search(b.first, match_b, re);
            int num_a = std::stoi(match_a.str());
            int num_b = std::stoi(match_b.str());
            return num_a < num_b;
        });

        for (auto& p : powers) {
            cout << p.first << " power: " << p.second << endl;
        }
    }

    void battle(string id1, string id2) {
        if (players.find(id1) != players.end() && players.find(id2) != players.end()) {
            double power1 = players[id1]->get_power();
            double power2 = players[id2]->get_power();

            if(power1 > power2 && power1 > power2 * 1.1){
                cout << id1 << " wins" << endl;
            } else if(power2 > power1 && power2 > power1 * 1.1){
                cout << id2 << " wins" << endl;
            } else {
                cout << "Draw" << endl;
            }
        }
    }
};

int main() {
    int n;
    cin >> n;
    System sys;
    for (int i = 0; i < n; i++) {
        string action;
        cin >> action;
        if (action == "Add") {
            string role, id;
            cin >> role >> id;
            sys.add(role, id);
        } else if (action == "Set") {
            string id, attribute;
            double value;
            cin >> id >> attribute >> value;
            sys.set(id, attribute, value);
        } else if (action == "Team") {
            string team_id;
            cin >> team_id;
            vector<string> player_ids;
            string line;
            getline(cin, line);
            stringstream ss(line);
            string id;
            while (ss >> id) {
                player_ids.push_back(id);
            }
            sys.add_team(team_id, player_ids);
        } else if (action == "Modify") {
            string team_id, attribute;
            double value;
            cin >> team_id >> attribute >> value;
            sys.adjust_team(team_id, attribute, value);
        } else if (action == "List") {
            string type;
            cin >> type;
            if (type == "Normal") {
                sys.list_normal();
            } else if (type == "Power") {
                sys.list_power();
            }
        } else if (action == "Upgrade") {
            string id;
            cin >> id;
            sys.upgrade(id);
        } else if (action == "Equip") {
            string id, type;
            double value;
            cin >> id >> type >> value;
            sys.equip(id, type, value);
        } else if (action == "PowerList") {
            sys.powerlist();
        } else if (action == "Battle") {
            string id1, id2;
            cin >> id1 >> id2;
            sys.battle(id1, id2);
        } else {
            cout << "Invalid action" << endl;
        }
    }
    return 0;
}