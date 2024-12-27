#include <Calculator.h>
#include <iostream>
using namespace std;

int main(){
    Calculator calculator;
    cout << "Enter the first number: ";
    cout << calculator.calculate("5 + 3 * ( 6 + 7 ) - 2") << endl;
    return 0;
}