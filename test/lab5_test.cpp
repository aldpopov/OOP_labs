#include <gtest/gtest.h>
#include "../src/lab5/Stack.cpp"
#include "../src/lab5/MemoryResource.cpp"

TEST(MemoryResourceTest, Allocate_and_deallocate) {
  MemoryResource memory_resource;
  void* ptr1 = memory_resource.allocate(100);
  ASSERT_NE(ptr1, nullptr);
  memory_resource.deallocate(ptr1, 100);
}

TEST(MemoryResourceTest, Reuse_deallocated_memory) {
  MemoryResource memory_resource;
  void* ptr1 = memory_resource.allocate(50);
  memory_resource.deallocate(ptr1, 50);
  void* ptr2 = memory_resource.allocate(50);
  ASSERT_NE(ptr2, nullptr);
  memory_resource.deallocate(ptr2, 50);
}

TEST(StackTest, Empty_stack) {
  MemoryResource memory_resource;
  Stack<int> stack{&memory_resource};
  ASSERT_TRUE(stack.empty());
  ASSERT_EQ(stack.get_size(), 0);
}

TEST(StackTest, Push_and_pop) {
  MemoryResource memory_resource;
  Stack<int> stack{&memory_resource};
  stack.push(1);
  stack.push(2);
  stack.push(3);
  ASSERT_FALSE(stack.empty());
  ASSERT_EQ(stack.get_size(), 3);
  ASSERT_EQ(stack.top(), 3);
  stack.pop();
  ASSERT_EQ(stack.top(), 2);
  stack.pop();
  ASSERT_EQ(stack.top(), 1);
  stack.pop();
  ASSERT_TRUE(stack.empty());
}

TEST(StackTest, Clear) {
  MemoryResource memory_resource;
  Stack<int> stack{&memory_resource};
  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.clear();
  ASSERT_TRUE(stack.empty());
  ASSERT_EQ(stack.get_size(), 0);
}

TEST(StackTest, Iterator) {
  MemoryResource memory_resource;
  Stack<int> stack{&memory_resource};
  stack.push(1);
  stack.push(2);
  stack.push(3);
  int i = 1;
  for (int x : stack) {
    ASSERT_EQ(x, i++);
  }
}