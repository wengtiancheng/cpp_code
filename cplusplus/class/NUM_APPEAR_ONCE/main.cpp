#include <cassert>
#include <functional>
#include <iomanip>
#include <iostream>
#include "Solution.h"

using namespace std;

void TEST_0();
void TEST_1();
void TEST_2();

#define REGISTER_TEST_CASE(name) {#name, name}

int main() {
    std::unordered_map<std::string, std::function<void()>>
        test_functions_by_name = {
        REGISTER_TEST_CASE(TEST_0),
        REGISTER_TEST_CASE(TEST_1),
        REGISTER_TEST_CASE(TEST_2)};
    std::string test_case_name;
    std::cin >> test_case_name;
    auto it = test_functions_by_name.find(test_case_name);
    assert(it != test_functions_by_name.end());
    auto fn = it->second;
    fn();
    return 0;
}

void TEST_0() {
    vector<int> nums = {2, 2, 1};
    cout << singleNumber(nums) << endl;
}

void TEST_1() {
    vector<int> nums = {1};
    cout << singleNumber(nums) << endl;
}

void TEST_2() {
    vector<int> nums = {1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6};
    cout << singleNumber(nums) << endl;
}