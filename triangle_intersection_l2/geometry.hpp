template <typename T>
std::istream& operator>>(std::istream& stream, point<T>& p)
{
    stream >> p.x >> p.y >> p.z;
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

/*template <typename T>
triangle<T>:: triangle(const point<T>& p0, const point<T>& p1, const point<T> p2)
{
    array[0] = p0;
    array[1] = p1;
    array[2] = p2;

    float dx1 = p1.x - p0.x, dy1 = p1.y - p0.y, dz1 = p1.z - p0.z;
    float dx2 = p2.x - p0.x, dy2 = p2.y - p0.y, dz2 = p2.z - p0.z;
    a_ = dy1*dz2 - dz1*dy2;
    b_ = dz1*dx2 - dx1*dz2;
    c_ = dx1*dy2 - dy1*dx2;
    d_ = (-1)*(a_*p0.x + b_*p0.y + c_*p0.z);

    std::cout << a_ << ' ' << b_ << ' ' << c_ << ' ' << d_ << '\n';
} */

template <typename T>
bool triangle<T>:: isbelong(const point<T>& p) const
{
    float dx = p.x - array[0].x, dy = p.y - array[0].y, dz = p.z - array[0].z;
    float dx1 = array[1].x - array[0].x, dy1 = array[1].y - array[0].y, dz1 = array[1].z - array[0].z;
    float dx2 = array[2].x - array[0].x, dy2 = array[2].y - array[0].y, dz2 = array[2].z - array[0].z;

    float a1 = dy1*dz2 - dz1*dy2, b1 = dz1*dx2 - dx1*dz2, c1 = dx1*dy2 - dy1*dx2;
    float a2 = dy1*dz - dz1*dy, b2 = dz1*dx - dx1*dz, c2 = dx1*dy - dy1*dx;
    float a3 = dy*dz2 - dz*dy2, b3 = dz*dx2 - dx*dz2, c3 = dx*dy2 - dy*dx2;

    float s = std::sqrt(a1*a1 + b1*b1 + c1*c1), s1 = std::sqrt(a2*a2 + b2*b2 + c2*c2);
    float s2 = std::sqrt(a3*a3 + b3*b3 + c3*c3), s3 = s - s1 - s2;

    float a = s1 / s, b = s2 / s, c = s3 / s;
    if (a >= 0 && b >= 0 && c >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool triangle<T>:: line_intersection(const line<T>& l)
{
    float dx = l.p2.x - l.p1.x, dy = l.p2.y - l.p1.y, dz = l.p2.z - l.p1.z;
    float dx1 = array[1].x - array[0].x, dy1 = array[1].y - array[0].y, dz1 = array[1].z - array[0].z;
    float dx2 = array[2].x - array[0].x, dy2 = array[2].y - array[0].y, dz2 = array[2].z - array[0].z;
    float a = dy1*dz2 - dz1*dy2, b = dz1*dx2 - dx1*dz2, c = dx1*dy2 - dy1*dx2;
    float d = a*array[0].x + b*array[0].y + c*array[0].z;

    float r = l.p1.x*dy - l.p1.y*dx, q = l.p1.x*dz - l.p1.z*dx;

    float det = dy*b*dx + dx*(dz*c + a*dx), detx = r*b*dx + dx*(q*c + d*dx);
    float dety = dy*(q*c + d*dx) - r*(dz*c + a*dx), detz = (-1)*dy*b*q + dx*(dz*d - a*q) + r*dz*b;

    if (det != 0)
    {
        point<T> tmp {detx / det, dety / det, detz / det};
        if (this->isbelong(tmp))
        {
            return true;
        }
    }
    else
    {
        float tmp = a*l.p1.x + b*l.p1.y + c*l.p1.z - d;
        if (tmp == 0)
        {
            return true;
        }
    }

    return false;
}

template <typename T>
bool triangle<T>:: triangle_intersection(const triangle<T>& tr)
{
    if (this->line_intersection({tr.array[0], tr.array[1]}) ||
        this->line_intersection({tr.array[1], tr.array[2]}) ||
        this->line_intersection({tr.array[2], tr.array[0]}))
    {
        return true;
    }
    
    return false;
}