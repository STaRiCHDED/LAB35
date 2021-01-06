// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>
#include "Stack.hpp"

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
