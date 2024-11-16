#include <iostream>
#include <string>
#include "./src/lab5/Stack.cpp"
#include "./src/lab5/MemoryResource.cpp"

using namespace std;

struct Struct_type {
    int id;
    std::string name;
};

int main() {
    MemoryResource custom_resource;
    Stack<int> int_stack(&custom_resource);
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    std::cout << "Int stack contents: ";
    for (auto& val : int_stack) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    Stack<Struct_type> complex_stack(&custom_resource);
    complex_stack.push({1, "Ivan"});
    complex_stack.push({2, "Andrew"});
    std::cout << "Complex stack contents: ";
    for (auto& val : complex_stack) {
        std::cout << "{ ind: " << val.id << ", name: " << val.name << " } ";
    }
    std::cout << std::endl;

    return 0;
}
