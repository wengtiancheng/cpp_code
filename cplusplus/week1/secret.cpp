#include <iostream>
#include <string>
#include <cctype>
using namespace std;

std::string key(const std::string& s, int k) {
    std::string cleaned;
    for (char c : s) {
        if (c != '-') {
            cleaned += std::toupper(c);
        }
    }

    int n = cleaned.size();
    if (n == 0) return "INVALID";

    int mid_size = n % k;
    if (mid_size == 0) mid_size = k;
    

    std::string res;
    for (int i = 0; i <= k * (k - 2); i += k ) {
        res += cleaned.substr(i, k);
        //对这一部分进行检查
        bool is_alpha = false;
        bool is_digit = false;
        for (int j = i; j < i + k; j++) {
            if (std::isalpha(cleaned[j])) {
                is_alpha = true;
            } else if (std::isdigit(cleaned[j])) {
                is_digit = true;
            }
        }
        if ( !is_alpha || ! is_digit) {
            return "INVALID";
        }
        res += '-';
    }
    res += cleaned.substr(k * (k - 1), mid_size);
    res += '-';
    for(int i = k * (k - 1) + mid_size; i < n - 1; i += k){
        res += cleaned.substr(i, k);
        //对这一部分进行检查
        bool is_alpha = false;
        bool is_digit = false;
        for (int j = i; j < i + k; j++) {
            if (std::isalpha(cleaned[j])) {
                is_alpha = true;
            } else if (std::isdigit(cleaned[j])) {
                is_digit = true;
            }
        }
        if ( !is_alpha || ! is_digit) {
            return "INVALID";
        }
        res += '-';
    }
    int len = res.length();
    res = res.substr(0, len - 1);
    return res;
    
    
    

}

int main() {
    std::string s;
    int k;
    cin >> s;
    cin >> k;

    std::string result = key(s, k);
    std::cout << result << std::endl;

    return 0;
}