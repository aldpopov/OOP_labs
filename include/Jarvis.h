#pragma once
#include <iostream>
#include <vector>
#include "Point.h"
#include "Figure.h"

int orientation(Point p, Point q, Point r);
Point* convex_hull(Figure& fig);