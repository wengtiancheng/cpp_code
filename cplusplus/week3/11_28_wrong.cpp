#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Store{
public:
    int Chicken;
    int Lettuce;
    int Tomato;
    int Cheese;
    int Onion;
    int Sauce;
    
    Store() : Chicken(0), Lettuce(0), Tomato(0), Cheese(0), Onion(0){}
    
    void add_stock(string name, int num){
        if(name == "Chicken"){
            Chicken += num;
        }else if(name == "Lettuce"){
            Lettuce += num;
        }else if(name == "Tomato"){
            Tomato += num;
        }else if(name == "Cheese"){
            Cheese += num;
        }else if(name == "Onion"){
            Onion += num;
        }else if(name == "Sauce"){
            Sauce += num;
        }
        
        cout << "Stocked " << name << " with " << num << " units" << endl;
    }
    
    void sub_stock(string name, int num){
        if(name == "Chicken"){
            Chicken -= num;
        }else if(name == "Lettuce"){
            Lettuce -= num;
        }else if(name == "Tomato"){
            Tomato -= num;
        }else if(name == "Cheese"){
            Cheese -= num;
        }else if(name == "Onion"){
            Onion -= num;
        }else if(name == "Sauce"){
            Sauce -= num;
        }
    }
    
    bool enough(string name, int num){
        if(name == "Chicken"){
            return Chicken >= num;
        }else if(name == "Lettuce"){
            return Lettuce >= num;
        }else if(name == "Tomato"){
            return Tomato >= num;
        }else if(name == "Cheese"){
            return Cheese >= num;
        }else if(name == "Onion"){
            return Onion >= num;
        }else if(name == "Sauce"){
            return Sauce >= num;
        }
    }
    
    void order(string id, vector<pair<string, int> list){
        bool tmp = true;
        vector<pair<string, int>> missing(0, nullptr);
        
        for(auto item : list){
            string name = item.first;
            int num = item.second;
            if(!enough(name, num)){
                int less = 
                
            }
            
        }
        if(tmp){
            cout << "Order " << id << " completed";
        }else{
            cout << "Order " << id << " failed: " << "missing "
            
        }
    }
    
    
    
    void inventory(){
        cout << "=== Inventory ===" << endl;
        cout << "Chicken: " << Chicken << endl;
        cout << "Lettuce: " << Lettuce << endl;
        cout << "Tomato: " << Tomato << endl;
        cout << "Cheese: " << Cheese << endl;
        cout << "Onion: " << Onion << endl;
        cout << "Sauce: " << Sauce << endl;
        cout << "=================" << endl;
    }
    
};

int main(){
    Store store = Store();
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        string command;
        cin >> command;
        if(command == "Stock"){
            string type;
            int num;
            store.add_stock(type, num);
            
        }else if(command == "Order"){
            string id;
            cin >> id;
            vector<pair<string, int>> list;
            Store.order()
            
        }else if(command =="Inventory"){
            store.inventory();
        }
    }
    return 0;
}