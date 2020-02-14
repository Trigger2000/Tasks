#include <fstream>
#include <cstdlib>
#include "geometry.h"

int getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0); 

    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void generate(int until, int& counter, int limit, std::ofstream& out)
{
    srand(static_cast<unsigned int>(time(0)));

    while (counter != until)
    {
        point<float> p1{getRandomNumber(0, limit), getRandomNumber(0, limit), getRandomNumber(0, limit)};
        point<float> p2{getRandomNumber(0, limit), getRandomNumber(0, limit), getRandomNumber(0, limit)};
        point<float> p3{getRandomNumber(0, limit), getRandomNumber(0, limit), getRandomNumber(0, limit)};
        float dx1 = p1.x - p2.x, dx2 = p1.x - p3.x, dx3 = p2.x - p3.x;
        float dy1 = p1.y - p2.y, dy2 = p1.y - p3.y, dy3 = p2.y - p3.y;
        float dz1 = p1.z - p2.z, dz2 = p1.z - p3.z, dz3 = p2.z - p3.z;

        float l1 = std::sqrt(dx1*dx1 + dy1*dy1 + dy1*dy1);
        float l2 = std::sqrt(dx2*dx2 + dy2*dy2 + dy2*dy2);
        float l3 = std::sqrt(dx3*dx3 + dy3*dy3 + dy3*dy3);
        if (l1 <= l2 + l3 && l2 <= l1 + l3 && l3 <= l1 + l2)
        {
            out << p1 << ' ' << p2 << ' ' << p3 << '\n';
            counter++;
        }
    }
}

int main()
{
    std::ofstream out;
    out.open("tests/9.dat"); 

    out << 10000 << '\n';

    int counter = 0;
    generate(3000, counter, 20, out);
    generate(7000, counter, 70, out);
    generate(10000, counter, 100, out);

    return 0;
}