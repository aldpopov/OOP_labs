#include <iostream>
#include "Octal.h"

using namespace std;

int main() {
    Octal octal_1("123");
    Octal octal_2("456");
    Octal octal_3 = octal_1;
    if(octal_1 < octal_2) {
        cout << "Passed." << endl;
    } else {
        cout << "Failed." << endl;
    }
    if(octal_1 == octal_2) {
        cout << "Passed." << endl;
    } else {
        cout << "Failed." << endl;
    }
    if(octal_1 > octal_2) {
        cout << "Passed." << endl;
    } else {
        cout << "Failed." << endl;
    }
    Octal sum = octal_1 + octal_2;
    sum.print();
    Octal subt = octal_2 - octal_1;
    subt.print();
    return 0;
}