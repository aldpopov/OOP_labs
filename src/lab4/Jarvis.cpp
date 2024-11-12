#include <iostream>
#include "Jarvis.h"
#include "Figure.h"
#include <memory>
using namespace std;


template <Number N>
int orientation(Point<N> p, Point<N> q, Point<N> r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if(val == 0) {
        return 0;
    }
    return (val > 0) ? 1 : 2;
}

template <Number N>
unique_ptr<Point<N>[]> convex_hull(Figure<N>& fig) {
    if (fig.vertex_quantity < 3) {
        throw std::invalid_argument("Less than 3 vertices.");
    }
    unique_ptr<Point<N>[]> hull = make_unique<Point<N>[]>(fig.size() + 1);
    int hull_size = 0;

    int l = 0;
    for (int i = 1; i < fig.size(); i++) {
        if (fig.vertices[i].x < fig.vertices[l].x) {
            l = i;
        }
    }
    int p = l, q;
    do {
        hull[hull_size++] = fig.vertices[p];
        q = (p + 1) % fig.size();
        for (int i = 0; i < fig.size(); i++) {
            if (orientation(fig.vertices[p], fig.vertices[i], fig.vertices[q]) == 2) {
                q = i;
            }
        }
        p = q;
    } while (p != l);
    unique_ptr<Point<N>[]> result = make_unique<Point<N>[]>(hull_size + 1);
    result[0].x = hull_size;
    result[0].y = 0;
    for(int i = 0; i < hull_size; i++) {
        result[i + 1] = hull[i];
    }
    return result;
}