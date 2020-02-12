#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

#define GREEN 0
#define RED 1

using std::vector;

template <typename T>
struct point
{
    T x = 0.0, y = 0.0, z = 0.0;
};

template<typename T>
std::istream& operator>>(std::istream& stream, point<T>& p);

template<typename T>
bool operator==(const point<T>& rhs, const point<T>& p);

template <typename T>
class line
{
public:
    point<T> p1, p2;
};

template <typename T>
class triangle
{
public:
    //triangle(const point<T>& p0, const point<T>& p1, const point<T> p2);
    bool isbelong(const point<T>& p) const;
    bool line_intersection(const line<T>& l);
    bool triangle_intersection(const triangle<T>& tr);

    point<T> array[3];
    //int a_ = 0, b_ = 0, c_ = 0, d_ = 0;
    int colour = GREEN;
};

template <typename T>
std::istream& operator>>(std::istream& stream, triangle<T>& tr);

#include "geometry.hpp"