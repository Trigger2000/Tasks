#include "declarations.h"

int main(int argc, char** argv) 
{
	if (argc < 2)
	{
		std::cout << "No input\n";
		exit(EXIT_FAILURE);
	}
	std::string filename(argv[1]);
	std::ifstream ifstream(filename);
	if (!ifstream)
	{
		std::cout << "Can't open file " << filename << '\n';
		exit(EXIT_FAILURE);
	}

	std::unordered_map<line, std::set<int>> bindings;
	std::vector<Triangle> triangles = ParseFile(ifstream, bindings);

	std::ofstream ofstream;
	ofstream.open("result.txt");
	find_neighbours(triangles, bindings, ofstream);

    return 0;
}

bool operator==(const line& l1, const line& l2)
{
	if (l1.begin_ == l2.begin_ && l1.end_ == l2.end_)
	{
		return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& stream, const point& pt)
{
	stream << '{' << pt.x_ << ", " << pt.y_ << ", " << pt.z_ << '}';
	return stream;
}

std::istream& operator>>(std::istream& stream, point& pt)
{
	stream >> pt.x_ >> pt.y_ >> pt.z_;
	return stream;
}

bool operator==(const point& p1, const point& p2)
{
	if (p1.x_ == p2.x_ && p1.y_ == p2.y_)
	{
		return true;
	}

	return false;
}

void find_neighbours(const std::vector<Triangle>& triangles, 
					const std::unordered_map<line, std::set<int>>& bindings, std::ostream& stream)
{

	for (const auto& item: triangles)
	{
		std::set<int> helper;
		line l1 = {item.pts_[0], item.pts_[1]};
		line l2 = {item.pts_[0], item.pts_[2]};
		line l3 = {item.pts_[1], item.pts_[2]};

		std::vector<std::set<int>> tmp = {bindings.at(l1), bindings.at(l2), bindings.at(l3)};

		for (const auto& it: tmp)
		{
			if (it.size() == 2)
			{
				if (*it.begin() == item.number_)
				{
					helper.insert(*std::prev(it.end()));
				}
				else
				{
					helper.insert(*it.begin());
				}
			}
		}
		
		int size = helper.size();
		while (size != 3)
		{
			stream << -1 << ' ';
			size++;
		}

		for (int i: helper)
		{
			stream << i << ' ';
		}
		stream << '\n';
	}
}

std::vector<Triangle> ParseFile(std::ifstream& stream, std::unordered_map<line, std::set<int>>& bindings)
{
	std::string rubbish;
	for (int i = 0; i < 4; ++i)
	{
		getline(stream, rubbish);
		rubbish.clear();
	}
	int size = 0;
	stream >> rubbish >> size >> rubbish;

	std::vector<point> points;
	points.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		stream >> points[i];
	}

	std::vector<Triangle> result;
	int triangles_amount = 0, rubbish1 = 0;
	stream >> rubbish >> triangles_amount >> rubbish1;
	result.reserve(triangles_amount);

	for (int i = 0; i < triangles_amount; ++i)
	{
		int p1 = 0, p2 = 0, p3 = 0;
		stream >> rubbish1 >> p1 >> p2 >> p3;
		result.push_back({{points[p1], points[p2], points[p3]}, i});

		bindings[{points[p1], points[p2]}].insert(i);
		bindings[{points[p1], points[p3]}].insert(i);
		bindings[{points[p2], points[p3]}].insert(i);
		bindings[{points[p2], points[p1]}].insert(i);
		bindings[{points[p3], points[p1]}].insert(i);
		bindings[{points[p3], points[p2]}].insert(i);
	}

	return result;
}