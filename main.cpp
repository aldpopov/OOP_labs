#include <iostream>
#include "Figure.h"
#include "Rhombus.h"
#include "Pentagon.h"
#include "Hexagon.h"
#include "Jarvis.h"

using namespace std;

void print_figs(Figure** figures) {
    for (int i = 0; i < 3; i++) {
        const Figure* figure = figures[i];
        if (figure != nullptr) {
            cout << *figure << endl << "area = " << double(*figure) << endl << "center = " << *(*figure).center() << endl;
            cout << endl;
        }
    }
}

int main() {
    Figure** figures = new Figure*[3];
    Rhombus* rhomb = new Rhombus();
    Pentagon* penta = new Pentagon();
    Hexagon* hex = new Hexagon();

    cout << "Enter coordinates for your rhombus: " << endl;
    cin >> *rhomb;
    figures[0] = rhomb;
    cout << "Enter coordinates for your pentagon: " << endl;
    cin >> *penta;
    figures[1] = penta;
    cout << "Enter coordinates for your hexagon: " << endl;
    cin >> *hex;
    figures[2] = hex;

    print_figs(figures);

    double total_area = 0;
    for(int i = 0; i < 3; i++) {
        total_area += double(*figures[i]);
    }
    cout << "Total area = " << total_area << endl;

    size_t index;
    cout << "Enter index of figure you want to delete: " << endl;
    cin >> index;

    if(index > 2 || index < 0) {
        cout << "Index is out of range" << endl;
        return 0;
    }

    delete figures[index];
    figures[index] = nullptr;
    print_figs(figures);
}