#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int minSubArrayLen(int n, vector<int>& nums, int target) {
    int l = 0, sum = 0;
    int min_len = INT_MAX; 
    int result_sum = INT_MAX; 

    for (int r = 0; r < n; ++r) {
        sum += nums[r];

        // 当当前窗口的和大于等于 target 时，尝试缩小窗口
        while (sum >= target) {
            int current_len = r - l + 1; // 当前子数组的长度
            int current_sum = l + r; // 当前左右下标和

            if (current_len < min_len || (current_len == min_len && current_sum < result_sum)) {
                min_len = current_len;
                result_sum = current_sum;
            }

            sum -= nums[l]; // 缩小窗口
            ++l;
        }
    }

    
    return result_sum == INT_MAX ? 0 : result_sum;
}

int main() {
    int n, target;
    
    // 输入正整数个数 n
    cin >> n;

    vector<int> nums(n);
    
    // 输入数组 nums
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }

    // 输入目标正整数 target
    cin >> target;

    // 调用函数计算最小子数组的左右下标和
    int result = minSubArrayLen(n, nums, target);

    // 输出结果
    cout << result << endl;

    return 0;
}
