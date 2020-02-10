#include "geometry.h"

int main()
{
    int amount = 0;
    std::cin >> amount;
    triangle<float>* array = (triangle<float>*)calloc(amount, sizeof(triangle<float>));
    for (int i = 0; i < amount; ++i)
    {
        cin >> array[i];
    }

    for (int i = 0; i < amount; ++i)
    {
        if (array[i].colour == RED)
        {
            continue;
        }

        for (int j = i; j < amount; ++j)
        {
            
        }

    }

    return 0;
}