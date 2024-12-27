//
// Created by wtc on 2024/12/25.
//
#include <iostream>
#include <string>
using namespace std;
class Person {
    // 成员变量和方法的声明
public:
  string name;
  int age;

  Person(): name(""), age(0){}
  Person(string name, int age) : name(name), age(age) {}
  Person(const Person& Other){
      this->age = Other.age;
      this->name = Other.name;
      cout << "Copy consturctor called" << endl;

  }

};

int main() {
    // 测试代码
    Person a = Person("fuck", 114);
    Person b = Person(a);
    cout << "name of b is" << b.name << endl;
    return 0;
}
