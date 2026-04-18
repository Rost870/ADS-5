// Copyright 2025 NNTU-CS
#include <string>
#include <cctype>
#include "tstack.h"

int priority(char op) {
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

bool isOp(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int apply(int a, int b, char op) {
  if (op == '+') return a + b;
  if (op == '-') return a - b;
  if (op == '*') return a * b;
  return a / b;
}

std::string infx2pstfx(const std::string& inf) {
  TStack<char, 100> ops;
  std::string out;

  for (size_t i = 0; i < inf.size(); ++i) {
    char c = inf[i];

    if (std::isdigit(c)) {
      while (i < inf.size() && std::isdigit(inf[i])) {
        out += inf[i];
        ++i;
      }
      out += ' ';
      --i;
    } else if (c == '(') {
      ops.push(c);
    } else if (c == ')') {
      while (!ops.empty() && ops.top() != '(') {
        out += ops.top();
        out += ' ';
        ops.pop();
      }
      if (!ops.empty()) {
        ops.pop();
      }
    } else if (isOp(c)) {
      while (!ops.empty() && ops.top() != '(' &&
             priority(ops.top()) >= priority(c)) {
        out += ops.top();
        out += ' ';
        ops.pop();
      }
      ops.push(c);
    }
  }

  while (!ops.empty()) {
    out += ops.top();
    out += ' ';
    ops.pop();
  }

  if (!out.empty()) {
    out.pop_back();
  }

  return out;
}

int eval(const std::string& post) {
  TStack<int, 100> nums;

  for (size_t i = 0; i < post.size(); ++i) {
    char c = post[i];

    if (c == ' ') {
      continue;
    }

    if (std::isdigit(c)) {
      int value = 0;
      while (i < post.size() && std::isdigit(post[i])) {
        value = value * 10 + (post[i] - '0');
        ++i;
      }
      nums.push(value);
      --i;
    } else if (isOp(c)) {
      int right = nums.top();
      nums.pop();

      int left = nums.top();
      nums.pop();

      nums.push(apply(left, right, c));
    }
  }

  return nums.top();
}
