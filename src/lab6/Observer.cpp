#include "Observer.h"

FileObserver::FileObserver(const std::string& filename) : file(filename, std::ios::app) {}

void FileObserver::update(const std::string& message) {
    file << message << std::endl;
}

void ScreenObserver::update(const std::string& message) {
    std::cout << message << std::endl;
}