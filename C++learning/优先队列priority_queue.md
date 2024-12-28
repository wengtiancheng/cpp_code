## 优先队列priority_queue



| 定义在头文件 `<queue>` 中                                    |      |      |
| ------------------------------------------------------------ | ---- | ---- |
| template<   class T,   class Container = [std::vector](https://cppreference.cn/w/cpp/container/vector)<T>,   class Compare = [std::less](https://cppreference.cn/w/cpp/utility/functional/less)<typename Container::value_type> > class priority_queue; |      |      |
|                                                              |      |      |

[优先级队列](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) 是一个 [容器适配器](https://cppreference.cn/w/cpp/container#Container_adaptors)，它以对数插入和提取为代价提供最大（默认）元素的常数时间查找。

可以提供用户提供的 `Compare` 来更改排序，例如使用 [std::greater](https://cppreference.cn/w/cpp/utility/functional/greater)<T> 将导致最小的元素显示为 [top()](https://cppreference.cn/w/cpp/container/priority_queue/top)。

使用 `priority_queue` 与在一些随机访问容器中管理 [堆](https://cppreference.cn/w/cpp/algorithm/make_heap) 类似，好处是无法意外地使堆失效。

### 模板参数

| T         | -    | 存储元素的类型。如果 `T` 与 `Container::value_type` 不是同一种类型，则程序格式错误。 |
| --------- | ---- | ------------------------------------------------------------ |
| Container | -    | 用于存储元素的底层容器的类型。容器必须满足 [*SequenceContainer*](https://cppreference.cn/w/cpp/named_req/SequenceContainer) 的要求，其迭代器必须满足 [*LegacyRandomAccessIterator*](https://cppreference.cn/w/cpp/named_req/RandomAccessIterator) 的要求。此外，它必须提供以下函数，具有 [通常的语义](https://cppreference.cn/w/cpp/named_req/SequenceContainer#Optional_operations)front()，例如 [std::vector::front()](https://cppreference.cn/w/cpp/container/vector/front)，push_back()，例如 [std::deque::push_back()](https://cppreference.cn/w/cpp/container/deque/push_back)，pop_back()，例如 [std::vector::pop_back()](https://cppreference.cn/w/cpp/container/vector/pop_back)。标准容器 [std::vector](https://cppreference.cn/w/cpp/container/vector)（包括 [`std::vector`](https://cppreference.cn/w/cpp/container/vector_bool)）和 [std::deque](https://cppreference.cn/w/cpp/container/deque) 满足这些要求。 |
| Compare   | -    | 提供严格弱排序的 [*Compare*](https://cppreference.cn/w/cpp/named_req/Compare) 类型。注意，[*Compare*](https://cppreference.cn/w/cpp/named_req/Compare) 参数的定义方式是，如果它的第一个参数在弱排序中位于第二个参数之前，则返回 true。但由于优先级队列首先输出最大元素，因此“位于之前”的元素实际上是最后输出的。也就是说，队列的头部包含根据 [*Compare*](https://cppreference.cn/w/cpp/named_req/Compare) 强加的弱排序的“最后一个”元素。 |

(摘自[cppreference](https://cppreference.cn/w/cpp/container/priority_queue))

**优先队列最大的特征就在于自动排序**



### 常见用法

常见的声明

```cpp
priority_queue <node> q;
//node是一个结构体
//结构体里重载了‘<’小于符号
priority_queue <int,vector<int>,greater<int> > q;
//不需要#include<vector>头文件
//注意后面两个“>”不要写在一起，“>>”是右移运算符
priority_queue <int,vector<int>,less<int> >q;

```

常见的操作

```cpp
q.size();//返回q里元素个数
q.empty();//返回q是否为空，空则返回1，否则返回0
q.push(k);//在q的末尾插入k
q.pop();//删掉q的第一个元素
q.top();//返回q的第一个元素

```





### 默认的优先队列

**非结构体结构**

```
priority_queue <int> q;
```

是按照从大到小的顺序排序的



**结构体结构（重载小于）**

```cpp
#include<cstdio>
#include<queue>
using namespace std;
struct node
{
	int x,y;
	bool operator < (const node & a) const
	{
		return x<a.x;
	}
}k;
priority_queue <node> q;
int main()
{
	k.x=10,k.y=100; q.push(k);
	k.x=12,k.y=60; q.push(k);
	k.x=14,k.y=40; q.push(k);
	k.x=6,k.y=80; q.push(k);
	k.x=8,k.y=20; q.push(k);
	while(!q.empty())
	{
		node m=q.top(); q.pop();
		printf("(%d,%d) ",m.x,m.y);
	}
}

```

最后输出的结果是(14,40) (12,60) (10,100) (8,20) (6,80)



### less和greater优先队列

```cpp
priority_queue<int,vector<int>,less<int> >q;
priority_queue<int,vector<int>,greater<int> >q;

```

差不多，第一个是从大到小，第二个是从小到大