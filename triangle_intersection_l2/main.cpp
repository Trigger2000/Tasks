#include "geometry.h"

int main()
{
    int amount = 0;
    std::cin >> amount;
    std::vector<triangle<float>> triangles;
    triangles.reserve(amount);
    for (int i = 0; i < amount; ++i)
    {
        point<float> p0, p1, p2;
        std::cin >> p0 >> p1 >> p2;
        triangle<float> tr(p0, p1, p2);
        triangles[i] = tr;
    }

    for (int i = 0; i < amount; ++i)
    {

        for (int j = i + 1; j < amount; ++j)
        {
            if ((triangles[i].color == colour::red && triangles[j].color == colour::red) ||
                triangles[i].color == colour::blue || triangles[j].color == colour::blue)
            {
                continue;
            }

            if (triangles[i].triangle_intersection(triangles[j]))
            {
                triangles[i].color = colour::red;
                triangles[j].color = colour::red;
            }
        }
    }

    for (int i = 0; i < amount; ++i)
    {
        if (triangles[i].color == colour::red)
        {
            std::cout << i << ' ';
        }
    } 

    std::cout << '\n';

    return 0;
}