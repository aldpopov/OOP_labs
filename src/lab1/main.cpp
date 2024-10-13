#include <iostream>

int plant(int up_speed, int down_speed, int desired_height) {
    if(up_speed <= 0 || down_speed <= 0 || desired_height < 0) {
        std::cout << "Incorrect input" << std::endl;
        return 0;
    }
    if(up_speed <= down_speed) {
        std::cout << "The plant is shrinking faster than growing" << std::endl;
        return 0;
    }
    int height = 0;
    int days = 0;
    while(height != desired_height) {
        height += up_speed;
        days++;
        if(height == desired_height) {
            return days;
        }
        height -= down_speed;
    }
    return days;
}