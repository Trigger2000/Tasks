#include "geometry.h"

int main()
{
    int amount = 0;
    std::cin >> amount;
    triangle<float>* array = static_cast<triangle<float>*>(calloc(amount, sizeof(triangle<float>)));
    for (int i = 0; i < amount; ++i)
    {
        /*point<float> p0, p1, p2;
        std::cin >> p0 >> p1 >> p2;
        triangle<float> tr(p0, p1, p2);
        array[i] = tr; */
        std::cin >> array[i];
    }

    for (int i = 0; i < amount; ++i)
    {

        for (int j = 0; j < amount; ++j)
        {
            if (i == j)
                continue;

            if (array[i].triangle_intersection(array[j]))
            {
                array[i].colour = RED;
                array[j].colour = RED;
            }
        }
    }

    for (int i = 0; i < amount; ++i)
    {
        if (array[i].colour == RED)
        {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';

    return 0;
}