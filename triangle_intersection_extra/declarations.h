#include <iostream>
#include <fstream>
#include <set>
#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

struct point final
{
	float x_ = 0.0, y_ = 0.0, z_ = 0.0;
};

struct line final
{
	point begin_, end_;
};

namespace std 
{
	template<>
	class hash<line> 
	{
	public:
		size_t operator()(const line &l) const
		{
		    size_t h1 = std::hash<float>()(l.begin_.x_);
		    size_t h2 = std::hash<float>()(l.begin_.y_);
			size_t h3 = std::hash<float>()(l.end_.x_);
			size_t h4 = std::hash<float>()(l.end_.y_);
		    return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
		}
	};
}

struct Triangle final
{
	std::vector<point> pts_;
	int number_;
};

std::istream& operator>>(std::istream& stream, point& pt);
std::ostream& operator<<(std::ostream& stream, const point& pt);
bool operator==(const point& p1, const point& p2);
bool operator==(const line& l1, const line& l2);
std::vector<Triangle> ParseFile(std::ifstream& stream, std::unordered_map<line, std::set<int>>& bindings);
void find_neighbours(const std::vector<Triangle>& triangles, 
					const std::unordered_map<line, std::set<int>>& bindings, std::ostream& stream);