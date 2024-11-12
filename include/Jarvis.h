#pragma once
#include <iostream>
#include "Point.h"
#include "Figure.h"

template <Number N>
int orientation(Point<N> p, Point<N> q, Point<N> r);

template <Number N>
std::unique_ptr<Point<N>[]> convex_hull(Figure<N>& fig);