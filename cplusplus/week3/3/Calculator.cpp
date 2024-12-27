#include "Calculator.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

using namespace std;

// 构造函数：初始化运算符优先级和函数表
Calculator::Calculator() {
  precedenceTable['+'] = 6;
  precedenceTable['-'] = 6;
  precedenceTable['*'] = 5;
  precedenceTable['/'] = 5;
  functionTable['+'] = [](double a, double b) { return a + b; };
  functionTable['-'] = [](double a, double b) { return a - b; };
  functionTable['*'] = [](double a, double b) { return a * b; };
  functionTable['/'] = [](double a, double b) { return a / b; };
}

// 注册常数
void Calculator::registerConstant(const string& symbol, double val) {
  constantTable[symbol] = val;
}

// 获取树节点值
double Calculator::getVal(TreeNode* node) {
  if (!node->left && !node->right) {
    // 叶节点
    if (constantTable.find(node->element) != constantTable.end()) {
      return constantTable[node->element];
    }
    return stod(node->element);
  }
  // 非叶节点
  return node->operate(getVal(node->left), getVal(node->right));
}

// 解析表达式为后缀表达式
vector<string> parseToPostfix(const string& expr, const map<char, int>& precedenceTable) {
  vector<string> postfix;
  stack<char> opStack;
  istringstream iss(expr);
  string token;
  while (iss >> token) {
    if (isdigit(token[0]) || isalpha(token[0])) {
      postfix.push_back(token);  // 操作数
    } else if (token == "(") {
      opStack.push('(');  // 左括号
    } else if (token == ")") {
      // 右括号
      while (!opStack.empty() && opStack.top() != '(') {
        postfix.push_back(string(1, opStack.top()));
        opStack.pop();
      }
      opStack.pop();  // 弹出左括号
    } else {
      // 运算符
      while (!opStack.empty() && precedenceTable.find(opStack.top()) != precedenceTable.end() &&
             precedenceTable.at(opStack.top()) <= precedenceTable.at(token[0])) {
        postfix.push_back(string(1, opStack.top()));
        opStack.pop();
      }
      opStack.push(token[0]);
    }
  }
  // 弹出栈中剩余运算符
  while (!opStack.empty()) {
    postfix.push_back(string(1, opStack.top()));
    opStack.pop();
  }
  return postfix;
}

// 构建表达式树
TreeNode* Calculator::buildTree(vector<string>& tokens) {
  stack<TreeNode*> nodeStack;
  for (const string& token : tokens) {
    if (isdigit(token[0]) || isalpha(token[0])) {
      nodeStack.push(new TreeNode(token));
    } else {
      TreeNode* right = nodeStack.top();
      nodeStack.pop();
      TreeNode* left = nodeStack.top();
      nodeStack.pop();
      nodeStack.push(new TreeNode(functionTable[token[0]], token, left, right));
    }
  }
  return nodeStack.top();
}

// 计算表达式
double Calculator::calculate(const string& expr) {
  vector<string> postfix = parseToPostfix(expr, precedenceTable);
  TreeNode* root = buildTree(postfix);
  double result = getVal(root);
  delete root;
  return result;
}

// 注册自定义运算符
void Calculator::registerOperator(const string& expr, int precedence) {
  istringstream iss(expr);
  string leftOperand, operatorSymbol, rightOperand, equals, expression;
  iss >> leftOperand >> operatorSymbol >> rightOperand >> equals;
  getline(iss, expression);

  // 替换自定义操作数
  auto treeTokens = parseToPostfix(expression, precedenceTable);
  TreeNode* opTree = buildTree(treeTokens);

  functionTable[operatorSymbol[0]] = [opTree, leftOperand, rightOperand, this](double a, double b) {
    constantTable[leftOperand] = a;
    constantTable[rightOperand] = b;
    return getVal(opTree);
  };
  precedenceTable[operatorSymbol[0]] = precedence;
}