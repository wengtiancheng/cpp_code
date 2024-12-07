#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
using namespace std;

class Comment {
public:
    double food_rating;
    double service_rating;
    double environment_rating;
    string date;
    string time;
    int version;
    Comment* next;
    Comment* parent;

    Comment(double food_rating, double service_rating, double environment_rating, string date, string time, int version, Comment* parent) : 
    food_rating(food_rating), service_rating(service_rating), environment_rating(environment_rating), date(date), time(time), version(version), parent(parent) {
        next = NULL;

    }
};

class Customer {
public:
    int id;
    Comment* current_comment;
    int version;

    Customer(int id) : id(id) {
        current_comment = NULL;
        version = 1;
    }

    ~Customer() {
    Comment* current = current_comment;
    while(current != NULL) {
        Comment* next = current->parent;  
        delete current;
        current = next;
    }
}



    void insert(double food_rating, double service_rating, double environment_rating, string date, string time) {
        Comment* new_comment = new Comment(food_rating, service_rating, environment_rating, date, time,  version, NULL);
        current_comment = new_comment;
        version++;
        
    }

    void modify(string dimension, double rating, string date, string time){
        double new_food_rating = current_comment->food_rating;
        double new_service_rating = current_comment->service_rating;
        double new_environment_rating = current_comment->environment_rating;
        if(dimension == "food"){
            new_food_rating = rating;
        } else if(dimension == "service"){
            new_service_rating = rating;
        } else if(dimension == "environment"){
            new_environment_rating = rating;
        }

        Comment* new_comment = new Comment(new_food_rating, new_service_rating, new_environment_rating, date, time, current_comment->version + 1, current_comment);
        
        current_comment = new_comment;
        
    }

    void history(string dimension){
        cout << "History:" << endl;
        Comment* temp = current_comment;
        while(temp != NULL){
            cout << "Version " << temp->version << ": ";
            if(dimension == "food"){
                cout << "Food Rating " <<  temp->food_rating << " ";
            } else if(dimension == "service"){
                cout << "Service Rating " <<  temp->service_rating << " ";
            } else if(dimension == "environment"){
                cout << "Environment Rating " <<  temp->environment_rating << " ";
            } else if(dimension == "all"){
                cout << "Food Rating " <<  temp->food_rating << " ";
                cout << "Service Rating " <<  temp->service_rating << " ";
                cout << "Environment Rating " <<  temp->environment_rating << " ";
            }
            cout << "Timestamp " << temp->date << " " << temp->time << endl;
            temp = temp->parent;
        }
    }
};

class System {
public:
    unordered_map<int, Customer*> customers;

    System(){}

    void insert(int customer_id, double food_rating, double service_rating, double environment_rating, string date, string time){
        if(customers.find(customer_id) == customers.end()){
            Customer* new_customer = new Customer(customer_id);
            new_customer->insert(food_rating, service_rating, environment_rating, date, time);
            customers[customer_id] = new_customer;
        }
       
        cout << "Review inserted successfully" << endl;
    }

    void modify(int customer_id, string dimension, double rating, string date, string time){
        if(customers.find(customer_id) == customers.end()){
            cout << "Customer ID not found, modification failed" << endl;
            return;
        }

        customers[customer_id]->modify(dimension, rating, date, time);
        cout << "Modification successful" << endl;
    }

    void delete_customer(int customer_id){
        if(customers.find(customer_id) == customers.end()){
            cout << "Customer ID not found, deletion failed" << endl;
            return;
        }

        delete customers[customer_id];
        customers.erase(customer_id);
        cout << "Deletion successful" << endl;
    }

    void history(int customer_id, string dimension){
        if(customers.find(customer_id) == customers.end()){
            
            return;
        }

        customers[customer_id]->history(dimension);
    }

   

    void display(string dimension){
        vector<pair<int, Comment*>> sorted_customers;
        for(auto& it :customers){
            if(it.second->current_comment == NULL){
                continue;
            }
            sorted_customers.push_back(make_pair(it.first, it.second->current_comment));
        }

        sort(sorted_customers.begin(), sorted_customers.end(), [](const pair<int, Comment*>& a, const pair<int, Comment*>& b) {
            if (a.second->date != b.second->date) {
                return a.second->date > b.second->date;
            } else {
                return a.second->time > b.second->time;
            }
        });
        for(auto& it : sorted_customers){
            cout << "Customer ID " << it.first << " ";
            if(dimension == "food"){
            cout << "Food Rating " << it.second->food_rating << " ";
            } else if(dimension == "service"){
            cout << "Service Rating " << it.second->service_rating << " ";
            } else if(dimension == "environment"){
            cout << "Environment Rating " << it.second->environment_rating << " ";
            } else if(dimension == "all"){
            cout << "Food Rating " << it.second->food_rating << " ";
            cout << "Service Rating " << it.second->service_rating << " ";
            cout << "Environment Rating " << it.second->environment_rating << " ";
            }
            cout << "Timestamp " << it.second->date << " " << it.second->time << endl;
        }

        
    }

    bool match_range(double rating, double lower, double upper){
        return rating >= lower && rating <= upper;
    }

    void range_query(double food_rating_lower, double food_rating_upper, double service_rating_lower, double service_rating_upper, double environment_rating_lower, double environment_rating_upper){
        vector<pair<int, Comment*>> sorted_customers;
    
        for(auto& it : customers){
            if(it.second->current_comment == NULL){
                continue;
            }
            if(match_range(it.second->current_comment->food_rating, food_rating_lower, food_rating_upper) && match_range(it.second->current_comment->service_rating, service_rating_lower, service_rating_upper) && match_range(it.second->current_comment->environment_rating, environment_rating_lower, environment_rating_upper)){
                sorted_customers.push_back(make_pair(it.first, it.second->current_comment));
            }
        }

        sort(sorted_customers.begin(), sorted_customers.end(), [](const pair<int, Comment*>&a , const pair<int, Comment*> &b) {
            return a.first > b.first;
        });

        for(auto& it : sorted_customers){
            cout << "Customer ID " << it.first << " ";
            cout << "Food Rating " <<  it.second->food_rating << " ";
            cout << "Service Rating " <<  it.second->service_rating << " ";
            cout << "Environment Rating " <<  it.second->environment_rating << " ";
            cout << "Timestamp " << it.second->date << " " << it.second->time << endl;
        }
    }



};

int main(){
    int n;
    cin >> n;
    System system = System();

    for(int i = 0; i < n; i++){
        string command;
        cin >> command;
        if(command == "insert"){
            int customer_id;
            double food_rating, service_rating, environment_rating;
            string date, time;
            cin >> customer_id >> food_rating >> service_rating >> environment_rating >> date >> time;
            system.insert(customer_id, food_rating, service_rating, environment_rating, date, time);
        } else if(command == "modify"){
            int customer_id;
            string dimension;
            double rating;
            string date, time;
            cin >> customer_id >> dimension >> rating >> date >> time;
            system.modify(customer_id, dimension, rating, date, time);
        } else if(command == "delete"){
            int customer_id;
            cin >> customer_id;
            system.delete_customer(customer_id);
        } else if(command == "history"){
            string input;
            getline(cin, input);
            istringstream iss(input);
            int customer_id;
            string dimension;
            //如果dimension没有输入，默认为all
            iss >> customer_id;
            if(!(iss >> dimension)){
                dimension = "all";
            }
            system.history(customer_id, dimension);
        } else if(command == "display"){
            string input;
            getline(cin, input);
            istringstream iss(input);
            string dimension;
            if(!(iss >> dimension)){
                dimension = "all";
            }
            system.display(dimension);
        } else if(command == "range_query"){
            double food_rating_lower, food_rating_upper, service_rating_lower, service_rating_upper, environment_rating_lower, environment_rating_upper;
            cin >> food_rating_lower >> food_rating_upper >> service_rating_lower >> service_rating_upper >> environment_rating_lower >> environment_rating_upper;
            system.range_query(food_rating_lower, food_rating_upper, service_rating_lower, service_rating_upper, environment_rating_lower, environment_rating_upper);
        }else{
            cout << "Invalid command" << endl;
        }
    }
    return 0;
}