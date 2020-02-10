#include "geometry.h"

int main()
{
    int amount = 0;
    std::cin >> amount;
    triangle<float>* array = static_cast<triangle<float>*>(calloc(amount, sizeof(triangle<float>)));
    for (int i = 0; i < amount; ++i)
    {
        std::cin >> array[i];
    }

    for (int i = 0; i < amount; ++i)
    {
        /*if (array[i].colour == RED)
        {
            continue;
        } */

        for (int j = i; j < amount; ++j)
        {
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
            std::cout << i;
        }
    }

    return 0;
}