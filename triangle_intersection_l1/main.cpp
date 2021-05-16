#include "geometry.h"

int main()
{
    triangle<double> tr1, tr2;
    std::cin >> tr1 >> tr2;
    
    Polygon<double> vertexes = find_points(tr1, tr2);
    
    if (vertexes.size() == 0)
    {
        std::cout << "No intersection\n";
    }
    else
    {
        std::cout << vertexes.count_area() << '\n';
    }
    
    return 0;
}