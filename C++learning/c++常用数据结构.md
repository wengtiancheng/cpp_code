## c++常用数据结构

### 1. 哈希表 ###

#### 适合场景：
- 需要快速的 **插入、删除和查找**（平均时间复杂度 `O(1)`）。
- 数据无序，对顺序没有要求。

#### 实现：
使用 `std::unordered_map` 或 `std::unordered_set`。

##### 示例（使用 `std::unordered_set` 删除某个元素）：

```cpp

#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<int> uset = {1, 2, 3, 4, 5};

    // 删除元素
    uset.erase(3);  // 删除值为3的元素

    // 查找元素
    if (uset.find(2) != uset.end()) {
        std::cout << "Found 2" << std::endl;
    }

    // 打印结果
    for (int val : uset) {
        std::cout << val << " ";
    }
    return 0;
}
```

#### 优缺点：

- **优点**：增删改查操作平均复杂度为 `O(1)`。
- **缺点**：不保持元素顺序。

------

### 2. 平衡二叉搜索树

#### 适合场景：

- 需要 **有序存储** 和 **快速查询**。
- 快速查找第 `k` 小或第 `k` 大的元素。

#### 实现：

使用 `std::set` 或 `std::map`，它们基于 **红黑树**，时间复杂度为 `O(log n)`。

##### 示例（使用 `std::set` 删除某个元素）：

```
cpp复制代码#include <iostream>
#include <set>

int main() {
    std::set<int> s = {1, 2, 3, 4, 5};

    // 删除元素
    s.erase(3);  // 删除值为3的元素

    // 插入元素
    s.insert(6);

    // 打印有序元素
    for (int val : s) {
        std::cout << val << " ";
    }
    return 0;
}
```

#### 优缺点：

- **优点**：元素有序，支持范围查询（例如查找某个范围内的元素）。
- **缺点**：增删查复杂度稍高，为 `O(log n)`。

------

### 3. 双向链表

#### 适合场景：

- 需要频繁的 **插入和删除操作**，尤其是非末尾位置的操作。
- 不需要频繁查找或随机访问。

#### 实现：

使用 `std::list`。

##### 示例（使用 `std::list` 删除某个元素）：

```
cpp复制代码#include <iostream>
#include <list>

int main() {
    std::list<int> lst = {1, 2, 3, 4, 5};

    // 删除元素
    lst.remove(3);  // 删除所有值为3的元素

    // 插入元素
    auto it = lst.begin();
    std::advance(it, 2);  // 移动到第3个位置
    lst.insert(it, 6);    // 在第3个位置插入6

    // 打印结果
    for (int val : lst) {
        std::cout << val << " ";
    }
    return 0;
}
```

#### 优缺点：

- **优点**：插入和删除操作高效（链表结构无需移动大量数据）。
- **缺点**：不支持随机访问，查找操作复杂度为 `O(n)`。

------

### 4. 动态数组

#### 适合场景：

- 需要随机访问和高效的末尾插入。
- 插入、删除集中在数组末尾。

#### 实现：

使用 `std::vector`。

##### 示例（按索引插入和删除）：

```
cpp复制代码#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 删除索引为2的元素
    vec.erase(vec.begin() + 2);

    // 插入元素到索引1
    vec.insert(vec.begin() + 1, 6);

    // 打印结果
    for (int val : vec) {
        std::cout << val << " ";
    }
    return 0;
}
```

#### 优缺点：

- **优点**：随机访问高效，插入和删除末尾的元素为 `O(1)`。
- **缺点**：在非末尾位置插入或删除元素会导致数据移动，复杂度为 `O(n)`。

------

### 5. 堆（优先队列）

#### 适合场景：

- 需要频繁地获取最大值或最小值。

#### 实现：

使用 `std::priority_queue`。

##### 示例（插入和删除最小元素）：

```
cpp复制代码#include <iostream>
#include <queue>

int main() {
    std::priority_queue<int> pq;

    // 插入元素
    pq.push(5);
    pq.push(2);
    pq.push(8);

    // 获取并删除最大元素
    while (!pq.empty()) {
        std::cout << pq.top() << " ";  // 打印最大值
        pq.pop();  // 删除最大值
    }

    return 0;
}
```

#### 优缺点：

- **优点**：插入和获取最大/最小值操作为 `O(log n)`。
- **缺点**：不支持查找或删除非顶端的元素。

------

### 总结对比

| 数据结构                     | 增删改查复杂度       | 是否有序 | 适用场景                           |
| ---------------------------- | -------------------- | -------- | ---------------------------------- |
| **原生数组**                 | 固定大小，需手动实现 | 否       | 简单固定大小的存储需求             |
| **`std::vector`**            | 插入/删除 `O(n)`     | 否       | 动态存储，末尾操作较多时更高效     |
| **`std::unordered_set/map`** | `O(1)`               | 否       | 需要快速查找和删除，无序存储       |
| **`std::set/map`**           | `O(log n)`           | 是       | 有序存储，范围查询                 |
| **`std::list`**              | 插入/删除 `O(1)`     | 否       | 频繁插入和删除，尤其非末尾位置操作 |
| **堆（`priority_queue`）**   | `O(log n)`           | 否       | 频繁获取最大/最小值                |

```
复制代码
直接将上述内容复制到 Typora 中，即可获得清晰的 Markdown 格式展示。
```