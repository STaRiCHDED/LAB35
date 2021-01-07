// Copyright 2020 Nikita Klimov nik179804@gmail.com

#include <gtest/gtest.h>
#include "Stack.hpp"
#include "StackT.hpp"

TEST(Stack, MovableClass) {
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
}

TEST(Stack, testCopy){
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
}

TEST(Stack, CopyPush) {
  Stack<int> stack;
  stack.push(static_cast<const int&>(5));
  stack.push(static_cast<const int&>(8));
  EXPECT_EQ(stack.head(), 8);
  stack.pop();
  EXPECT_EQ(stack.head(), 5);
}

TEST(Stack, Pop) {
  Stack<int> stack;
  EXPECT_ANY_THROW(stack.pop());
}

TEST(Stack, MovePush) {
  Stack<int> stack;
  stack.push(1);
  EXPECT_EQ(stack.head(), 1);
}

TEST(Stack, Head) {
  Stack<int> stack;
  EXPECT_ANY_THROW(stack.head());
}

TEST(StackT, MovableClass) {
  EXPECT_TRUE(std::is_move_constructible<StackT<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<StackT<int>>::value);
}

TEST(StackT, NonCopyedClass) {
  EXPECT_FALSE(std::is_copy_constructible<StackT<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<StackT<int>>::value);
}

TEST(StackT, Pop) {
  StackT<int> stack;
  EXPECT_ANY_THROW(stack.pop());
}

TEST(StackT,WrongMovePush) {
  StackT<int> stack;
  EXPECT_ANY_THROW(stack.push(1););
}

class Ex {
 public:
  int x;
  Ex() = default;
  Ex(int x1) : x(x1) {}
  Ex(Ex&& value) noexcept = default;
  Ex(const Ex& value) = delete;
  auto operator=(Ex&& value) noexcept -> Ex& = default;
  auto operator=(const Ex& value) -> Ex& = delete;
};
TEST(Ex, RightClass) {
  EXPECT_TRUE(std::is_move_constructible<Ex>::value);
  EXPECT_FALSE(std::is_copy_constructible<Ex>::value);
}

TEST(StackT, AddElement) {
  StackT<Ex> stack;
  stack.push(Ex(2));
  stack.push_emplace(Ex(3));
  EXPECT_EQ(stack.head().x, 3);
  stack.pop();
  EXPECT_EQ(stack.head().x, 2);
}
