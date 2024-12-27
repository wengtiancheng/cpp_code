## c++中自定义比较函数的编写

在C++中，自定义比较函数主要是为排序（例如 `std::sort`）提供自定义的排序规则。编写自定义比较函数时，可以使用以下三种方式：

------

### **1. 使用普通函数**

自定义一个普通函数，定义排序规则。

#### 示例

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 普通函数定义排序规则
bool compare(const pair<string, double>& a, const pair<string, double>& b) {
    return a.second < b.second;  // 按 `double` 的值升序排序
}

int main() {
    vector<pair<string, double>> data = {{"A", 3.4}, {"B", 1.2}, {"C", 5.6}};
    sort(data.begin(), data.end(), compare);

    for (const auto& item : data) {
        cout << item.first << ": " << item.second << endl;
    }
    return 0;
}
```

#### 特点

- **灵活**：可以在多个地方复用函数。
- **适合复杂逻辑**：适合需要多层逻辑判断的场景。

------

### **2. 使用函数对象（仿函数）**

通过定义一个类或结构体，并重载 `operator()`，实现自定义比较逻辑。

#### 示例

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 函数对象（仿函数）定义排序规则
struct Compare {
    bool operator()(const pair<string, double>& a, const pair<string, double>& b) const {
        return a.second > b.second;  // 按 `double` 的值降序排序
    }
};

int main() {
    vector<pair<string, double>> data = {{"A", 3.4}, {"B", 1.2}, {"C", 5.6}};
    sort(data.begin(), data.end(), Compare());

    for (const auto& item : data) {
        cout << item.first << ": " << item.second << endl;
    }
    return 0;
}
```

#### 特点

- **灵活**：支持在类中存储状态，用于调整排序逻辑。
- **推荐场景**：排序规则需要参数化时非常适用。

------

### **3. 使用 Lambda 表达式**

C++11 提供了 Lambda 表达式，可以直接定义一个匿名函数，非常简洁。

#### 示例

```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<string, double>> data = {{"A", 3.4}, {"B", 1.2}, {"C", 5.6}};

    // Lambda 表达式定义排序规则
    sort(data.begin(), data.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second < b.second;  // 按 `double` 的值升序排序
    });

    for (const auto& item : data) {
        cout << item.first << ": " << item.second << endl;
    }
    return 0;
}
```

#### 特点

- **简洁**：适合小型的、一次性的比较逻辑。
- **适合现代 C++**：推荐在短小排序逻辑中使用。
- lambda表达式中的参数来自于sort(或者find_if之类中的迭代器)

------

### **写自定义比较函数时的关键点**

#### 1. **参数类型**

- 通常为 `const` 引用类型，例如：`const pair<string, double>&`，避免拷贝开销。
- 参数个数固定为两个，分别表示两个需要比较的元素。

#### 2. **返回值类型**

- 必须返回布尔值（`bool`）。
- 返回 `true` 表示 `a` 应排在 `b` 前面，返回 `false` 表示 `a` 应排在 `b` 后面。

#### 3. **具体逻辑**

根据需求，比较规则可以多样化：

- **简单比较**: 按值、字母排序等。
- **组合比较**: 按多种字段进行排序，例如先按 `string` 排序，再按 `double` 排序。
- **特殊逻辑**: 从字符串提取数字，或对浮点数取整比较等。

#### 示例：从字符串提取数字进行排序

```c++
#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

int main() {
    vector<pair<string, double>> data = {{"item20", 1.2}, {"item3", 3.4}, {"item10", 2.5}};

    // Lambda 表达式定义排序规则
    sort(data.begin(), data.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        // 提取数字部分
        regex re("\\d+");
        smatch match_a, match_b;
        regex_search(a.first, match_a, re);
        regex_search(b.first, match_b, re);

        int num_a = stoi(match_a.str());
        int num_b = stoi(match_b.str());

        return num_a < num_b;  // 按提取的数字升序排序
    });

    for (const auto& item : data) {
        cout << item.first << ": " << item.second << endl;
    }
    return 0;
}
```

#### 运行结果

```
makefile复制代码item3: 3.4
item10: 2.5
item20: 1.2
```

------

### 总结

- **普通函数**：适合复杂逻辑、多次使用的场景。
- **仿函数**：适合需要状态或参数化的场景。
- **Lambda 表达式**：推荐用于短小的、局部的排序逻辑，现代 C++ 中的首选方式。