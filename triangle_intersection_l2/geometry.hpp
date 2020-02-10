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

template <typename T>
bool triangle<T>:: isbelong(const point<T>& p) const
{
    double dx = p.x - array[0].x, dy = p.y - array[0].y, dz = p.z - array[0].z;
    double dx1 = array[1].x - array[0].x, dy1 = array[1].y - array[0].y, dz1 = array[1].z - array[0].z;
    double dx2 = array[2].x - array[0].x, dy2 = array[2].y - array[0].y, dz2 = array[2].z - array[0].z;

    double a1 = dy1*dz2 - dz1*dy2, b1 = dz1*dx2 - dx1*dz2, c1 = dx1*dy2 - dy1*dx2;
    double a2 = dy1*dz - dz1*dy, b2 = dz1*dx - dx1*dz, c2 = dx1*dy - dy1*dx;
    double a3 = dy*dz2 - dz*dy2, b3 = dz*dx2 - dx*dz2, c3 = dx*dy2 - dy*dx2;

    double s = std::sqrt(a1*a1 + b1*b1 + c1*c1), s1 = std::sqrt(a2*a2 + b2*b2 + c2*c2);
    double s2 = std::sqrt(a3*a3 + b3*b3 + c3*c3), s3 = s - s1 - s2;

    double a = s1 / s, b = s2 / s, c = s3 / s;
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
bool line_triangle_intersection(const line<T>& l, const triangle<T>& tr, point<T>& p)
{
    double dx = l.p2.x - l.p1.x, dy = l.p2.y - l.p1.y, dz = l.p2.z - l.p1.z;
    double dx1 = tr.array[1].x - tr.array[0].x, dy1 = tr.array[1].y - tr.array[0].y, dz1 = tr.array[1].z - tr.array[0].z;
    double dx2 = tr.array[2].x - tr.array[0].x, dy2 = tr.array[2].y - tr.array[0].y, dz2 = tr.array[2].z - tr.array[0].z;
    double a = dy1*dz2 - dz1*dy2, b = dz1*dx2 - dx1*dz2, c = dx1*dy2 - dy1*dx2;

    double p = l.p2.x*dy - l.p2.y*dx, q = l.p2.x*dz - l.p2.z*dx;
    double r = a*tr.array[0].x + b*tr.array[0].y + c*tr.array[0].z;

    double det = dy*b*dx + dx*(dz*c + a*dx), detx = p*b*dx + dx*(q*c + r*dx);
    double dety = dy*(q*c + r*dx) - p*(dz*c + a*dx), detz = dy*(-b*q) + dx*(dz*r - a*q) + p*dz*b;

    if (det != 0)
    {
        point<T> tmp (detx / det, dety / det, detz / det);
        if (tr.isbelong(&tmp))
        {
            return true;
        }
    }
    else
    {
        double tmp = a*p1.x + b*p1.y + c*p1.z - r;
        if (tmp == 0)
        {
            return true;
        }
    }

    return false;
}