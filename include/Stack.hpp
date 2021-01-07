// Copyright 2020 Nikita Klimov nik179804@gmail.com

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <stdexcept>
#include <utility>

template <class T>
struct Element {
  T value;
  Element<T> *previous = nullptr;
};

template <typename T>
class Stack {
 public:
  Stack() = default;
  Stack(Stack &&st) noexcept = default;
  Stack(const Stack &st) = delete;

  auto operator=(Stack &&st) noexcept -> Stack & = default;
  auto operator=(const Stack &st) -> Stack & = delete;

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  ~Stack();

 protected:
  Element<T> *head_ = nullptr;
};

template <typename T>
void Stack<T>::push(T &&value) {
  auto *newElement = new Element<T>{std::forward<T>(value), head_};
  head_ = newElement;
}

template <typename T>
void Stack<T>::push(const T &value) {
  auto *newElement = new Element<T>{value, head_};
  Stack<T>::head_ = newElement;
}

template <typename T>
void Stack<T>::pop() {
  if (head_) {
    auto *upper = head_;
    head_ = head_->previous;
    delete upper;
  } else {
    throw std::out_of_range("Empty Stack");
  }
}

template <typename T>
const T &Stack<T>::head() const {
  if (!head_) {
    throw std::out_of_range("Empty Stack");
  }
  return head_->value;
}

template <typename T>
Stack<T>::~Stack(){
    while (head_ != nullptr)
      pop();
}
#endif // INCLUDE_STACK_H_