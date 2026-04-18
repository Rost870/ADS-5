// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
class TStack {
 private:
  static const int kMaxSize = size;
  T data[kMaxSize];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  bool empty() const {
    return topIndex == -1;
  }

  bool full() const {
    return topIndex == kMaxSize - 1;
  }

  void push(const T& value) {
    if (!full()) {
      data[++topIndex] = value;
    }
  }

  void pop() {
    if (!empty()) {
      --topIndex;
    }
  }

  T top() const {
    return data[topIndex];
  }
};

#endif  // INCLUDE_TSTACK_H_
