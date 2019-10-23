template <typename T>
std::istream& operator>>(std::istream& stream, point<T>& p)
{
    stream >> p.x >> p.y;
    return stream;
}

template <typename T>
std::istream& operator>>(std::istream& stream, triangle<T>& tr)
{
    stream >> tr.array[0] >> tr.array[1] >> tr.array[2];
    return stream;
}

template <typename T>
bool operator==(const point<T>& lhs, const point<T>& rhs)
{
    if (lhs.x == rhs.x && lhs.y == rhs.y)
        return true;
    else
        return false;
}

template<typename T>
Polygon<T> find_points(const triangle<T>& tr1, const triangle<T>& tr2)
{
    Polygon<T> intersections;
    for (int i = 0; i < 3; i++)
    {
        if (isbelong(tr1.array[i], tr2) == 1 && 
            std::find(intersections.begin(), intersections.end(), tr1.array[i]) == intersections.end())
        {
            intersections.push_back(tr1.array[i]);
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (isbelong(tr2.array[i], tr1) &&
            std::find(intersections.begin(), intersections.end(), tr2.array[i]) == intersections.end())
            intersections.push_back(tr2.array[i]);
    }
    
    line<T> lines1[3] = {{tr1.array[0], tr1.array[1]}, {tr1.array[0], tr1.array[2]}, {tr1.array[1], tr1.array[2]}};
    line<T> lines2[3] = {{tr2.array[0], tr2.array[1]}, {tr2.array[0], tr2.array[2]}, {tr2.array[1], tr2.array[2]}};
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            point<T> p;
            bool res = line_intersection(lines1[i], lines2[j], p);
            if (res == true && 
                std::find(intersections.begin(), intersections.end(), p) == intersections.end())
                intersections.push_back(p);
        }
    } 
    
    return intersections;
}

template <typename T>
bool isbelong(const point<T>& p, const triangle<T>& tr)
{
    double dx1 = tr.array[1].x - tr.array[0].x, dx2 = tr.array[2].x - tr.array[0].x;
    double dy1 = tr.array[1].y - tr.array[0].y, dy2 = tr.array[2].y - tr.array[0].y;
    double dx = p.x - tr.array[0].x, dy = p.y - tr.array[0].y;
    double det = dx1*dy2 - dy1*dx2, det1 = dx*dy2 - dy*dx2, det2 = dx1*dy - dy1*dx;
    double a = det1 / det, b = det2 / det, c = (det - det1 - det2) / det;
    
    if (a >= 0 && b >= 0 && c >= 0)
        return true;
    else
        return false;
}

template <typename T>
bool line_intersection(const line<T>& l1, const line<T>& l2, point<T>& p)
{
    double a1 = l1.p2.y - l1.p1.y, b1 = l1.p1.x - l1.p2.x, c1 = l1.p1.x * a1 + l1.p1.y * b1;
    double a2 = l2.p2.y - l2.p1.y, b2 = l2.p1.x - l2.p2.x, c2 = l2.p1.x * a2 + l2.p1.y * b2;
    
    double det = a1*b2 - a2*b1, det1 = c1*b2 - c2*b1, det2 = a1*c2 - a2*c1;
    
    if (det != 0)
    {
        double x = det1 / det;
        double y = det2 / det;
        if (x >= std::min(l1.p1.x, l1.p2.x) && x <= std::max(l1.p1.x, l1.p2.x) &&
            x >= std::min(l2.p1.x, l2.p2.x) && x <= std::max(l2.p1.x, l2.p2.x) &&
            y >= std::min(l1.p1.y, l1.p2.y) && y <= std::max(l1.p1.y, l1.p2.y) &&
            y >= std::min(l2.p1.y, l2.p2.y) && y <= std::max(l2.p1.y, l2.p2.y))
        {
            p.x = x;
            p.y = y;
            return true;
        }
        
        return false;
    }
    
    return false;
}

template <typename T>
double Polygon<T>:: count_area ()
{
    anticlockwise_sort();
    
    double res = 0.0;
    for (int i = 0; i < vertexes.size() - 1; i++)
    {
        res += (vertexes[i + 1].x - vertexes[i].x) * (vertexes[i + 1].y + vertexes[i].y) / 2;
    }
    res += (vertexes[0].x - vertexes[vertexes.size() - 1].x) * (vertexes[0].y + vertexes[vertexes.size() - 1].y) / 2;
    
    return std::abs(res);
}

template <typename T>
void Polygon<T>:: anticlockwise_sort()
{
    std::sort(vertexes.begin(), vertexes.end(), [](const point<T>& lhs, const point<T>& rhs)
    {
        return lhs.x < rhs.x;
    });
    
    double ymin = vertexes[0].y, xmin = vertexes[0].x;
    int pos = 0;
    for (int i = 0; vertexes[i].x == xmin; i++)
    {
        if (vertexes[i].y < ymin)
        {
            ymin = vertexes[i].y;
            pos = i;
        }
    }
    
    if (pos != 0)
    {
        std::swap(vertexes[0], vertexes[pos]);
    }
    
    point<T> p0 = vertexes[0];
    std::sort(vertexes.begin()++, vertexes.end(), [p0](const point<T>& lhs, const point<T>& rhs)
    {
        double dy_lhs = lhs.y - p0.y, dx_lhs = lhs.x - p0.x;
        double dy_rhs = rhs.y - p0.y, dx_rhs = rhs.x - p0.x;
        
        return std::atan(dy_lhs / dx_lhs) < std::atan(dy_rhs / dx_rhs);
    });
}
