#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


double answer(double a, double b, double left, double right);
double left_func(double x);
double right_func(double a, double b, double x);

int main() {
    double a, b;
    cin >> a >> b;

    // 调用 answer 函数并打印结果
    cout << fixed << setprecision(6) << answer(a, b, 0, 10) << endl;

    return 0;
}

// 递归计算答案
double answer(double a, double b, double left, double right) {
    double mid = (left + right) / 2;
    if (right - left <= 1e-7) {
        return mid;
    } else {
        double value_mid = left_func(mid) - right_func(a, b, mid);
        if (b >= 1) {
            if (value_mid > 0) {
                return answer(a, b, left, mid);
            } else {
                return answer(a, b, mid, right);
            }
        } else {
            if (value_mid > 0) {
                return answer(a, b, mid, right);
            } else {
                return answer(a, b, left, mid);
            }
        }
    }
}

// 左边函数
double left_func(double x) {
    return exp(x); // e 的 x 次方
}

// 右边函数
double right_func(double a, double b, double x) {
    return a * x + b;
}