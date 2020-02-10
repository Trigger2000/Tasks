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
struct line
{
    point<T> p1, p2;
};

template <typename T>
struct triangle
{
    point<T> array[3];
    int colour = GREEN;

    bool isbelong(const point<T>& p) const;
};

template <typename T>
std::istream& operator>>(std::istream& stream, triangle<T>& tr);

template <typename T>
bool line_triangle_intersection(const line<T>& l, const triangle<T>& tr, point<T>& p);

#include "geometry.hpp"