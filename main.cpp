#include <iostream>
#include "./src/lab4/Jarvis.cpp"
#include "./src/lab4/Point.cpp"
#include "./src/lab4/Figure.cpp"
#include "./src/lab4/Rhombus.cpp"
#include "./src/lab4/Pentagon.cpp"
#include "./src/lab4/Hexagon.cpp"
#include "./src/lab4/Array.cpp"

using namespace std;

template <typename Type>
void print_figs(Array<Type> figures) {
    if(figures.size() != 0) {
        for (int i = 0; i < figures.size(); i++) {
            auto& figure = *figures[i];
            cout << figure << endl << "area = " << double(figure) << endl << "center = " << *(figure).center() << endl;
            cout << endl;
        }
    }
}

int main() {
    Array<Figure<double>> array;
    Rhombus<double> rhomb;
    Pentagon<double> penta;
    Hexagon<double> hex;

    cout << "Enter coordinates for your rhombus: " << endl;
    cin >> rhomb;
    array.append(std::make_shared<Rhombus<double>>(rhomb));
    cout << "Enter coordinates for your pentagon: " << endl;
    cin >> penta;
    array.append(std::make_shared<Pentagon<double>>(penta));
    cout << "Enter coordinates for your hexagon: " << endl;
    cin >> hex;
    array.append(std::make_shared<Hexagon<double>>(hex));

    print_figs(array);

    double total_area = 0;
    for(int i = 0; i < array.size(); i++) {
        const std::shared_ptr<Figure<double>> figure = array[i];
        total_area += double(*figure);
    }
    cout << "Total area = " << total_area << endl;

    size_t index;
    cout << "Enter index of figure you want to delete: " << endl;
    cin >> index;
    array.remove(index);
    print_figs(array);
}