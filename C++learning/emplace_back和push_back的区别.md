## emplace_back和push_back的区别

两者的用法相同

```cpp
values.push_back(1);
values.emplace_back(2);
```



两者的区别主要在于底层逻辑上

push_back()向容器尾部添加元素的时候，会首先创建这个元素，再将它拷贝或者移动到容器中

emplace_back()在实现时，则是直接在容器尾部创建这个元素，舍去了拷贝或者移动元素的过程

示例代码

```cpp
#include <vector> 
#include <iostream> 
using namespace std;
class testDemo
{
public:
    testDemo(int num):num(num){
        std::cout << "调用构造函数" << endl;
    }
    testDemo(const testDemo& other) :num(other.num) {
        std::cout << "调用拷贝构造函数" << endl;
    }
    testDemo(testDemo&& other) :num(other.num) {
        std::cout << "调用移动构造函数" << endl;
    }
private:
    int num;
};

int main()
{
    cout << "emplace_back:" << endl;
    std::vector<testDemo> demo1;
    demo1.emplace_back(2);  

    cout << "push_back:" << endl;
    std::vector<testDemo> demo2;
    demo2.push_back(2);
}

```

最后运行的结果为

```
emplace_back:
调用构造函数
push_back:
调用构造函数
调用移动构造函数

```

如果把移动构造函数注释掉，可以发现push_back调用的是拷贝构造函数，说明push_back()在底层实现的时候会优先调用拷贝构造函数