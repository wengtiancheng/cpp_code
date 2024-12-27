## lambda表达式

在 C++ 中，**Lambda 表达式**（匿名函数）是一个非常强大的功能，允许你在代码中定义函数并立即使用它们。Lambda 表达式的语法具有几个部分，每一部分都有其特定的含义。下面是 Lambda 表达式的详细解释：

### Lambda 表达式的基本语法

```
[捕获列表](参数列表) -> 返回类型 {函数体}
```

### 1. **捕获列表（Capture List）**

捕获列表位于方括号 `[]` 内，指定了 Lambda 表达式如何访问外部作用域中的变量。捕获列表可以捕获外部变量并将其传递到 Lambda 表达式中。

#### 语法示例：

```
[捕获方式]变量1, 变量2, ...
```

#### 捕获方式：

- 值捕获（By Value）

  ：

  ```
  [=]
  ```

   或 

  ```
  [x]
  ```

  - 捕获外部变量的副本。
  - 示例：[ `x`, `y` ] 捕获 `x` 和 `y` 的副本。
  - 示例：[ `=` ] 捕获所有外部变量的副本。

- 引用捕获（By Reference）

  ：

  ```
  [&]
  ```

   或 

  ```
  [&x]
  ```

  - 捕获外部变量的引用。
  - 示例：[ `&` ] 捕获所有外部变量的引用。
  - 示例：[ `&x` ] 只捕获 `x` 的引用。

- 混合捕获（混合值和引用）

  ：

  ```
  [=, &x]
  ```

  - 捕获外部变量的副本，但对某些变量使用引用。
  - 示例：[ `=, &x` ] 捕获所有外部变量的副本，但对 `x` 捕获引用。

#### 示例：

```
int x = 10, y = 20;
auto lambda = [x, y]() {
    cout << x << ", " << y << endl;
};
lambda();  // 输出 10, 20
```

------

### 2. **参数列表（Parameter List）**

在括号 `()` 中，定义了 Lambda 表达式接受的参数，类似于普通函数的参数列表。参数可以是任意类型和数量，甚至可以为空。

#### 示例：

```
[] (int a, double b) -> void {
    // do something
}
```

- 参数列表可以为空：`[]() {}`，这表示该 Lambda 不接受任何参数。
- 也可以接收多个参数，如：`[] (int a, double b) {}`，这里的 Lambda 接收 `int` 和 `double` 类型的参数。

#### 示例：

```
auto add = [](int a, int b) {
    return a + b;
};
cout << add(3, 4);  // 输出 7
```

------

### 3. **返回类型（Return Type）**

箭头 `->` 后面是 Lambda 表达式的返回类型。如果 Lambda 表达式返回值类型能够通过自动推导推断出来，可以省略这一部分；如果需要指定返回类型，则必须显式声明。

#### 语法：

```
[]() -> int { return 10; }
```

#### 示例：

```
auto square = [](int x) -> int {
    return x * x;
};
cout << square(5);  // 输出 25
```

- 如果 Lambda 表达式的返回类型可以从表达式推导出来，`->` 后面的类型可以省略。

  ```
  auto add = [](int a, int b) {
      return a + b;  // 自动推导返回类型为 int
  };
  cout << add(2, 3);  // 输出 5
  ```

------

### 4. **函数体（Function Body）**

函数体 `{}` 中包含 Lambda 表达式的逻辑。Lambda 表达式的函数体和普通函数的函数体一样，可以包含任何 C++ 代码。

#### 示例：

```
auto print = [](int a) { cout << "Value: " << a << endl; };
print(10);  // 输出 Value: 10
```

------

### 综合示例：

假设我们有以下代码段，它演示了如何使用 Lambda 表达式来处理外部变量和参数：

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int factor = 2;
    std::vector<int> nums = {1, 2, 3, 4, 5};

    // 使用 Lambda 表达式捕获外部变量并修改其值
    auto multiply = [factor](int n) -> int {
        return n * factor;
    };

    // 使用 Lambda 表达式将每个数字乘以 factor
    std::transform(nums.begin(), nums.end(), nums.begin(), multiply);

    for (int num : nums) {
        std::cout << num << " ";  // 输出 2 4 6 8 10
    }
    std::cout << std::endl;

    // 修改捕获的变量
    factor = 3;
    auto multiply_new = [factor](int n) -> int {
        return n * factor;
    };

    std::transform(nums.begin(), nums.end(), nums.begin(), multiply_new);

    for (int num : nums) {
        std::cout << num << " ";  // 输出 6 12 18 24 30
    }

    return 0;
}
```

### 解析：

1. **捕获变量**：`[factor]` 捕获外部变量 `factor`，使得 Lambda 可以在其函数体内使用 `factor` 的值。
2. **参数列表**：`(int n)` 表示 Lambda 接受一个 `int` 类型的参数。
3. **返回类型**：`-> int` 表示 Lambda 返回一个 `int` 类型的值。
4. **函数体**：`return n * factor;` 在 Lambda 内部实现了数字乘法。

Lambda 表达式的结构包括以下四个部分，每一部分的含义和作用：

1. **捕获列表**：用于捕获外部变量，可以按值或引用捕获。
2. **参数列表**：定义 Lambda 表达式接收的参数，类似于普通函数的参数。
3. **返回类型**：定义 Lambda 表达式的返回类型，通常可以自动推导，也可以显式指定。
4. **函数体**：包含 Lambda 表达式执行的逻辑。

Lambda 表达式是一种简洁而强大的工具，特别是在需要传递函数或在算法中使用自定义条件时，非常有用。



### 5. **关于 lambda 表达式中的多个参数：**

当您在 `std::sort` 或类似的算法中使用 lambda 表达式时，lambda 会有多个参数，因为这些算法会将多个元素传递给 lambda 进行比较或处理。例如，`std::sort` 会将两个元素传递给 lambda，作为参数来进行比较。

#### 示例：`std::sort` 中的 lambda 表达式

```cpp
std::sort(messages.begin(), messages.end(), [](const Message& a, const Message& b) {
    return a.priority < b.priority;  // 按优先级进行排序
});
```

- **`a` 和 `b`**：这两个参数分别是 `std::sort` 中待比较的两个元素。在排序时，`std::sort` 会反复调用这个 lambda，传递不同的元素对 `a` 和 `b`，然后根据返回的值决定排序顺序。

### 6. **在 lambda 表达式中参数的来源：**

- **`std::sort`**：这个算法会在排序过程中将容器中的两个元素传递给 lambda。每次比较时，这两个元素会被作为参数传递给 lambda。
- **`std::find_if` 和其他 STL 算法**：这些算法会将容器中的元素依次传递给 lambda 表达式。与 `std::sort` 不同，`std::find_if` 通常只传递一个元素。

### 7. **总结：**

- **`lambda` 的参数由调用的算法提供**：在 `std::sort` 中，算法会传递两个元素作为参数给 lambda。在其他算法（如 `std::find_if`）中，lambda 可能只接收一个元素作为参数。
- **在 `std::sort` 中，`lambda` 需要两个参数**，代表容器中的两个元素，通常用于比较它们的大小或顺序。
- **`lambda` 可以捕获外部变量**：除了传递给 lambda 的参数外，您还可以通过捕获列表来访问外部作用域的变量。

### 

