#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int id;
    Student() : name(" "), id(0) {}
    Student(string name, int id) : name(name), id(id) {}
    // 成员变量和方法
};

int main() {
    shared_ptr<Student> a = make_shared<Student>("fuck", 114);
    shared_ptr<Student> b = a;
    cout << "Student of a ref count" << a.use_count() << endl;
    cout << "Student of b ref count" <<b.use_count() << endl;
    // 测试代码
    return 0;
}
