#include "geometry.h"

int main()
{
    int amount = 0;
    std::cin >> amount;
    triangle<float>* triangles = static_cast<triangle<float>*>(calloc(amount, sizeof(triangle<float>)));
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
            if (triangles[i].colour == RED && triangles[j].colour == RED)
            {
                continue;
            }

            if (triangles[i].triangle_intersection(triangles[j]))
            {
                triangles[i].colour = RED;
                triangles[j].colour = RED;
            }
        }
    }

    for (int i = 0; i < amount; ++i)
    {
        if (triangles[i].colour == RED)
        {
            std::cout << i << ' ';
        }
    } 

    std::cout << '\n';

    return 0;
}