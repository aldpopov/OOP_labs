#include <iostream>

#include "plant.h"

using namespace std;

int main() {
    int up_speed, down_speed, desired_height;
    std::cout << "Enter speed of growth, speed of shrinking and plant's desired height: " << std::endl;
    std::cin >> up_speed >> down_speed >> desired_height;
    std::cout << plant(up_speed, down_speed, desired_height) << std::endl;
}
