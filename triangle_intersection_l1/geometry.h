#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>

using std::vector;

template <typename T>
struct point
{
    T x = 0.0, y = 0.0;
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

    bool isbelong(const point<T>& p) const;
};

template <typename T>
std::istream& operator>>(std::istream& stream, triangle<T>& tr);


template <typename T>
class Polygon 
{
    vector<point<T>> vertexes;
    
public:
    void anticlockwise_sort();
    double count_area();

    int size() const
    {
        return vertexes.size();
    }

    void push_back(const point<T>& p)
    {
        vertexes.push_back(p);
    }

    typename vector<point<T>>::iterator begin()
    {
        return vertexes.begin();
    }

    typename vector<point<T>>::iterator end()
    {
        return vertexes.end();
    }
};


template <typename T>
Polygon<T> find_points(const triangle<T>& tr1, const triangle<T>& tr2);

template <typename T>
bool line_intersection(const line<T>& l1, const line<T>& l2, point<T>& p);

#include "geometry.hpp"