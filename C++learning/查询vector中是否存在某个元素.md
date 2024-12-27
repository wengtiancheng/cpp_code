## 查询vector中是否存在某个元素

### 1、std::count 

#include   <algorithm>

如果只需要知道特定元素的数量，比较合适，如果数量为0，则表示不存在该元素

```cpp
vector<int> v{ 4, 7, 9, 1, 2, 5 };
		int key = 2;
		
		if (count(v.begin(), v.end(), key))
		{
				cout << "Element found" << endl;
		}
		else
		{
				cout << "Element NOT found" << endl;
		}

```



### 2、std::find

find会在查找到指定值之后返回

```c++
if(std::find(v.begin(), v.end(), key) != v.end())
```





### 3、std::find_if

有点大材小用，用来查询满足特定条件的元素

```c++
if(std::find_if(v.begin(), v.end(), [](int i){return i > 1 && i < 3}) != v.end())
```

返回找到的第一个符合条件的值的迭代器



### 4、std::any_of

与上一个类似，但是返回bool值



### 5、std::binary_search

先排序，再使用二分查找

