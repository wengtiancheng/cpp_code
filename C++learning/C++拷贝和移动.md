## C++拷贝和移动

在C++中，拷贝（copy）和移动（move）是两种不同的对象传递和赋值机制，主要区别在于是否涉及资源的“拷贝”或“转移”。下面是它们的主要区别及如何区分它们：

### 1. **拷贝（Copy）**

拷贝是指创建一个新对象，并且将源对象的值（或状态）复制到新对象中。拷贝通常需要进行深拷贝，即将对象的数据完全复制到新对象中。

- **拷贝构造函数**：当创建一个新对象并用已有对象初始化时，调用拷贝构造函数。

  ```
  cpp复制代码T t1;
  T t2 = t1;  // 使用拷贝构造函数
  ```

- **拷贝赋值运算符**：当一个已存在的对象被另一个对象赋值时，调用拷贝赋值运算符。

  ```
  cpp复制代码T t1, t2;
  t2 = t1;  // 使用拷贝赋值运算符
  ```

### 2. **移动（Move）**

移动是指将一个对象的资源（如内存、文件句柄等）转移给另一个对象，而不是复制。移动操作比拷贝更高效，因为它避免了不必要的数据复制。

- **移动构造函数**：当一个对象通过“移动”初始化另一个对象时，调用移动构造函数。通常是通过 `std::move` 来显式标记对象为可移动。

  ```
  cpp复制代码T t1;
  T t2 = std::move(t1);  // 使用移动构造函数
  ```

- **移动赋值运算符**：当一个已存在的对象通过“移动”从另一个对象获得资源时，调用移动赋值运算符。

  ```
  cpp复制代码T t1, t2;
  t2 = std::move(t1);  // 使用移动赋值运算符
  ```

### 3. **如何区分移动和拷贝**

在代码中，**拷贝**和**移动**的区别主要通过以下方式区分：

- **拷贝**发生时，源对象的数据会被复制到目标对象。拷贝构造函数和拷贝赋值运算符接受的是常量引用 `const T&` 类型。
- **移动**发生时，源对象的数据被“转移”到目标对象，源对象的资源不再有效，且不再需要复制。移动构造函数和移动赋值运算符接受的是右值引用 `T&&` 类型。

### 示例代码

```
cpp复制代码#include <iostream>
#include <vector>

class MyClass {
public:
    MyClass() {
        std::cout << "Constructor\n";
    }

    ~MyClass() {
        std::cout << "Destructor\n";
    }

    // 拷贝构造函数
    MyClass(const MyClass& other) {
        std::cout << "Copy Constructor\n";
    }

    // 移动构造函数
    MyClass(MyClass&& other) noexcept {
        std::cout << "Move Constructor\n";
    }

    // 拷贝赋值运算符
    MyClass& operator=(const MyClass& other) {
        std::cout << "Copy Assignment\n";
        return *this;
    }

    // 移动赋值运算符
    MyClass& operator=(MyClass&& other) noexcept {
        std::cout << "Move Assignment\n";
        return *this;
    }
};

int main() {
    MyClass obj1;                   // 调用构造函数
    MyClass obj2 = obj1;             // 调用拷贝构造函数
    MyClass obj3 = std::move(obj1);  // 调用移动构造函数

    std::vector<MyClass> vec;
    vec.push_back(obj2);             // 调用拷贝构造函数
    vec.push_back(std::move(obj2));  // 调用移动构造函数

    MyClass obj4;
    obj4 = obj3;                     // 调用拷贝赋值
    obj4 = std::move(obj3);          // 调用移动赋值
}
```

### 输出：

```
rust复制代码Constructor
Copy Constructor
Move Constructor
Copy Constructor
Move Constructor
Copy Assignment
Move Assignment
```

### 总结

- 拷贝

  是指将一个对象的内容复制到另一个对象中。

  - 拷贝构造函数和拷贝赋值运算符通常以 `const T&` 为参数。

- 移动

  是指将一个对象的资源转移给另一个对象。

  - 移动构造函数和移动赋值运算符通常以 `T&&` 为参数。

通过 `std::move` 可以显式地将一个对象标记为右值，这时移动操作会被优先选择。如果没有 `std::move`，则编译器会默认执行拷贝操作。