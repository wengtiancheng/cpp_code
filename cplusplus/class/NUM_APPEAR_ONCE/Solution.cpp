#include "Solution.h"

#include <iostream>
#include <unordered_set>
using namespace std;

int singleNumber(std::vector<int>& nums) {
    // TODO
    unordered_set<int> tmp = {};
    int len = nums.size();
    for(int i = 0; i < len; i++) {
        if(tmp.find(nums[i]) != tmp.end()) {
            tmp.erase(nums[i]);
        }else {
            tmp.insert(nums[i]);
        }
    }
    if (!tmp.empty()) {
        cout << *tmp.begin() << endl; // Print the first element
    }
    return 0;
}