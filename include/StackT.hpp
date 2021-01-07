// Copyright 2020 Nikita Klimov nik179804@gmail.com

#ifndef INCLUDE_STACKT_H_
#define INCLUDE_STACKT_H_

#include "Stack.hpp"


template <typename T>
class StackT : public Stack<T> {
 public:
  void push(T &&value);
  T pop();
  template <typename... Args>
  void push_emplace(Args &&... value);
};

template <typename T>
void StackT<T>::push(T &&value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *newElement = new Element<T>{std::forward<T>(value), Stack<T>::head_};
  Stack<T>::head_ = newElement;
}

template <typename T>
T StackT<T>::pop() {
  if (!Stack<T>::head_) {
    throw std::out_of_range("Empty Stack!!!");
  }
  auto *upper = Stack<T>::head_;
  Stack<T>::head_ = Stack<T>::head_->previous;
  T value = std::move(upper->value);
  delete upper;
  return value;
}

template <typename T>
template <typename... Args>
void StackT<T>::push_emplace(Args &&... value) {
  if (std::is_copy_constructible<T>::value ||
      std::is_copy_assignable<T>::value) {
    throw std::bad_typeid();
  }
  auto *newElement = new Element<T>{{std::forward<Args>(value)...}, Stack<T>::head_};
  Stack<T>::head_ = newElement;
}

#endif  // INCLUDE_STACKT_H_
