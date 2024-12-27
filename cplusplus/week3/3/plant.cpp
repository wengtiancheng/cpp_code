#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class plant {
public:
    
    int x;
    int y;

    plant(int x, int y) : x(x), y(y) {}

    virtual ~plant() {}

    virtual string get_type() const = 0;

};

class pea : public plant {
public:
    int hp;
    int atk;

    pea(int hp, int atk, int x, int y) : plant(x, y), hp(hp), atk(atk) {}


    string get_type() const override {
        return "pea";
    }
};

class nut : public plant {
public:
    int hp;

    nut(int hp, int x, int y) : plant(x, y), hp(hp) {}
    string get_type() const override {
        return "nut";
    }
};
class potato : public plant {
public:
    int atk;
    int active;

    potato(int atk, int x, int y) : plant(x, y), atk(atk), active(0) {}
    void activate() {
        this->active = 1;
    }
    string get_type() const override {
        return "potato";
    }
};

class zombie{
public:
    int hp;
    int atk;
    int speed;
    int x;
    int y;

    zombie(int hp, int atk, int speed, int x) : hp(hp), atk(atk), speed(speed), x(x), y(9) {}
    

    
    


};

class System{
public:
    vector<vector<plant*>> plant_map;
    vector<vector<vector<zombie*>>> zombie_map;
    int count_of_plant;
    int count_of_zombie;
    int cycle;
    int zombie_win;

    System(){
        plant_map.resize(5, vector<plant*>(10, nullptr));
        zombie_map.resize(5, vector<vector<zombie*>>(10));
        count_of_plant = 0;
        count_of_zombie = 0;
        cycle = 1;
        zombie_win = 0;
    }
    ~System() {
        for (int i = 0; i < plant_map.size(); ++i) {
            for (int j = 0; j < plant_map[i].size(); ++j) {
                delete plant_map[i][j];
            }
        }
        for (int i = 0; i < zombie_map.size(); ++i) {
            for (int j = 0; j < zombie_map[i][j].size(); ++j) {
                for (zombie* z : zombie_map[i][j]) {
                    delete z;
                }
            }
        }
    }

    void add_pea(int hp, int atk, int x, int y){
        plant_map[x][y] = new pea(hp, atk, x, y);
        count_of_plant++;
    }
    void add_nut(int hp, int x, int y){
        plant_map[x][y] = new nut(hp, x, y);
        count_of_plant++;
    }
    void add_potato(int atk, int x, int y){
        plant_map[x][y] = new potato(atk, x, y);
        count_of_plant++;
    }
    void add_zombie(int hp, int atk, int speed, int x){
        zombie* z = new zombie(hp, atk, speed, x);
        zombie_map[x][9].push_back(z);
        count_of_zombie++;
    }

    void pea_attack(pea& attacker){
        int x = attacker.x;
        int y = attacker.y;
        for(int i = y; i <= 9; i++){
            if(!zombie_map[x][i].empty()){
                vector<zombie*> zombies_to_delete;
                for (zombie* z : zombie_map[x][i]) {
                    z->hp -= attacker.atk;
                    if (z->hp <= 0) {
                        zombies_to_delete.push_back(z);
                    }
                }
                for (zombie* z : zombies_to_delete) {
                    auto it = find(zombie_map[x][i].begin(), zombie_map[x][i].end(), z);
                    if (it != zombie_map[x][i].end()) {
                        zombie_map[x][i].erase(it);
                        delete z;
                        count_of_zombie--;
                    }
                }
                break;
            }
        }

    }
    void potato_bomb(potato& boom) {
        if(boom.active == 0) {

        }else {
            //对周围3*3的区域进行攻击
            for(int i = boom.x - 1; i <= boom.x + 1; i++) {
                for(int j = boom.y - 1; j <= boom.y + 1; j++) {
                    if(i >= 0 && i < 5 && j >= 0 && j <= 9) {
                        if(!zombie_map[i][j].empty()) {
                            for(zombie* z : zombie_map[i][j]) {
                                z->hp -= boom.atk;
                                if(z->hp <= 0) {
                                    auto it = find(zombie_map[i][j].begin(), zombie_map[i][j].end(), z);
                                    if(it != zombie_map[i][j].end()) {
                                        zombie_map[i][j].erase(it);
                                        delete z;
                                        count_of_zombie--;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //攻击完后自身消失
            plant_map[boom.x][boom.y] = nullptr;
            count_of_plant--;

        }

    }
    void zombie_move(zombie& invader) {
        int x = invader.x;
        int y = invader.y;
        int before = invader.y;
        bool stopped = false;
        //当前所处的位置是否有植物
        if(plant_map[x][y] != nullptr && plant_map[x][y]->get_type() != "potato") {
            stopped = true;
        }else {
            for (int i = 1; i <= invader.speed; ++i) {
                int new_y = y - i;
                if (new_y < 0) {
                    zombie_win = 1;
                    return;
                }
                if (plant_map[x][new_y] != nullptr && plant_map[x][new_y]->get_type() != "potato") {
                    stopped = true;
                    invader.y = new_y;
                    break;
                }
                if(plant_map[x][new_y] != nullptr && plant_map[x][new_y]->get_type() == "potato"){
                    dynamic_cast<potato&>(*plant_map[x][new_y]).activate();

                }
            }

            if (!stopped) {
                invader.y -= invader.speed;
            }

            auto it = find(zombie_map[x][before].begin(), zombie_map[x][before].end(), &invader);
            if (it != zombie_map[x][before].end()) {
                zombie_map[x][invader.y].push_back(&invader);
                zombie_map[x][before].erase(it);
            }

            // 如果单元格中有土豆雷,需要激活，然后在下个回合中引爆
            if (plant_map[x][invader.y] != nullptr && plant_map[x][invader.y]->get_type() == "potato") {
                dynamic_cast<potato&>(*plant_map[x][invader.y]).activate();
            }
        }


    }
    void zombie_attack1(zombie& invader, pea& protecter){
        protecter.hp -= invader.atk;
        if(protecter.hp <= 0){
            int x = protecter.x;
            int y = protecter.y;
            plant_map[x][y] = nullptr;
            count_of_plant--;
        }
        
    }
    void zombie_attack2(zombie& invader, nut& protecter){
        protecter.hp -= invader.atk;
        if(protecter.hp <= 0){
            int x = protecter.x;
            int y = protecter.y;
            plant_map[x][y] = nullptr;
            count_of_plant--;
        }
        
    }

    void print_status() const{
        cout << cycle << " " << count_of_plant << " " << count_of_zombie << endl;
        
    }

    void work(){
        while(1){
            for(int x = 0; x < 5; x++){
                for(int y = 0; y <= 9; y++){
                    if(plant_map[x][y] != nullptr && plant_map[x][y]->get_type() == "pea"){
                        pea_attack(dynamic_cast<pea&>(*plant_map[x][y]));
                    }
                    if(plant_map[x][y] != nullptr && plant_map[x][y]->get_type() == "potato"){
                        potato_bomb(dynamic_cast<potato&>(*plant_map[x][y]));
                    }
                    
                }
            }

            for(int x = 0; x < 5; x++){
                for(int y = 0; y <= 9; y++){
                    if(!zombie_map[x][y].empty()){
                        for (auto it = zombie_map[x][y].rbegin(); it != zombie_map[x][y].rend(); ++it) {
                            zombie* z = *it;
                            zombie_move(*z);
                        }

                    }
                }
            }

            for(int x = 0; x < 5; x++){
                for(int y = 0; y <= 9; y++){
                    if(plant_map[x][y] != nullptr && !zombie_map[x][y].empty()){
                        if(plant_map[x][y]->get_type() == "pea"){
                            for(zombie* z : zombie_map[x][y]){
                                zombie_attack1(*z, dynamic_cast<pea&>(*plant_map[x][y]));

                            }
                        }else if(plant_map[x][y]->get_type() == "nut"){
                            for(zombie* z : zombie_map[x][y]){
                                zombie_attack2(*z, dynamic_cast<nut&>(*plant_map[x][y]));
                            }
                        }
                    }
                }
            }
            print_status();


            if(count_of_zombie == 0){
                cout << "plants win" << endl;
                break;
            }else if(zombie_win == 1){
                cout << "zombies win" << endl;
                break;
            }
            cycle++;

        }
        
        
    }

};

int main(){
    int p, z;
    cin >> p >> z;
    System sys;
    for(int i = 0; i < p; i++){
        string type;
        cin >> type;
        if(type == "pea"){
            int hp, atk, x, y;
            cin >> hp >> atk >> x >> y;
            sys.add_pea(hp, atk, x, y);

        }else if(type == "nut"){
            int hp, x, y;
            cin >> hp >> x >> y;
            sys.add_nut(hp, x, y);

        }else if(type == "potato"){
            int atk, x, y;
            cin >> atk >> x >> y;
            sys.add_potato(atk, x, y);
        }

    }
    for(int i = 0; i < z; i++){
        int hp, atk, speed, x;
        cin >> hp >> atk >> speed >> x;
        sys.add_zombie(hp, atk, speed, x);

    }
    sys.work();
    return 0;
}