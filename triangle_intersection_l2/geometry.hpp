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
std::ostream& operator<<(std::ostream& stream, point<T>& p)
{
    stream << p.x << ' ' << p.y << ' ' << p.z;
    return stream;
}

template<typename T>
bool operator==(const point<T>& p1, const point<T>& p2)
{
    if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
triangle<T>:: triangle(const point<T>& p0, const point<T>& p1, const point<T>& p2)
{
    float dx1 = p1.x - p0.x, dy1 = p1.y - p0.y, dz1 = p1.z - p0.z;
    float dx2 = p2.x - p0.x, dy2 = p2.y - p0.y, dz2 = p2.z - p0.z;
    float dx3 = p2.x - p1.x, dy3 = p2.y - p1.y, dz3 = p2.z - p1.z;
    float l1 = std::sqrt(dx1*dx1 + dy1*dy1 + dz1*dz1);
    float l2 = std::sqrt(dx2*dx2 + dy2*dy2 + dz2*dz2);
    float l3 = std::sqrt(dx3*dx3 + dy3*dy3 + dz3*dz3);

    if (l1 >= l2 + l3 || l2 >= l1 + l3 || l3 >= l1 + l2)
    {
        color = colour::blue;
    }
    else
    {
        array[0] = p0;
        array[1] = p1;
        array[2] = p2;
        a_ = dy1*dz2 - dz1*dy2;
        b_ = dz1*dx2 - dx1*dz2;
        c_ = dx1*dy2 - dy1*dx2;
        d_ = a_*p0.x + b_*p0.y + c_*p0.z;
    }
}

template <typename T>
bool triangle<T>:: isbelong(const point<T>& p) const
{
    float dx = p.x - array[0].x, dy = p.y - array[0].y, dz = p.z - array[0].z;
    float dx1 = array[1].x - array[0].x, dy1 = array[1].y - array[0].y, dz1 = array[1].z - array[0].z;
    float dx2 = array[2].x - array[0].x, dy2 = array[2].y - array[0].y, dz2 = array[2].z - array[0].z;
    float dx10 = array[1].x - p.x, dy10 = array[1].y - p.y, dz10 = array[1].z - p.z;
    float dx20 = array[2].x - p.x, dy20 = array[2].y - p.y, dz20 = array[2].z - p.z;

    float a1 = dy1*dz2 - dz1*dy2, b1 = dz1*dx2 - dx1*dz2, c1 = dx1*dy2 - dy1*dx2;
    float a2 = dy1*dz - dz1*dy, b2 = dz1*dx - dx1*dz, c2 = dx1*dy - dy1*dx;
    float a3 = dy*dz2 - dz*dy2, b3 = dz*dx2 - dx*dz2, c3 = dx*dy2 - dy*dx2;
    float a4 = dy10*dz20 - dy20*dz10, b4 = dz10*dx20 - dz20*dx10, c4 = dx10*dy20 - dx20*dy10;

    float s = std::sqrt(a1*a1 + b1*b1 + c1*c1), s1 = std::sqrt(a2*a2 + b2*b2 + c2*c2);
    float s2 = std::sqrt(a3*a3 + b3*b3 + c3*c3), s3 = std::sqrt(a4*a4 + b4*b4 + c4*c4);
    float tmp = s - s1 - s2 - s3;
    if (tmp > -0.0001 && tmp < 0.0001)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool triangle<T>:: triangle_line_intersection(const line<T>& l) const
{
    float dx = l.p2.x - l.p1.x, dy = l.p2.y - l.p1.y, dz = l.p2.z - l.p1.z;
    float q = 0.0, r = 0.0, det = 0.0, detx = 0.0, dety = 0.0, detz = 0.0;
    if (dx <= -0.0001 || dx >= 0.0001)
    {
        q = l.p1.x*dy - l.p1.y*dx;
        r = l.p1.x*dz - l.p1.z*dx;
        det = a_*dx*dx + b_*dx*dy + c_*dx*dz;
        detx = d_*dx*dx + b_*q*dx + c_*r*dx;
        dety = -a_*q*dx + d_*dx*dy + c_*(dy*r - dz*q);
        detz = -a_*dx*r - b_*(dy*r - dz*q) + d_*dz*dx;
    }
    else if (dy <= -0.0001 || dy >= 0.0001)
    {
        q = l.p1.x*dy - l.p1.y*dx;
        r = l.p1.y*dz - l.p1.z*dy;
        det = a_*dx*dy + b_*dy*dy + c_*dy*dz;
        detx = d_*dx*dy + b_*q*dy + c_*(q*dz + r*dx);
        dety = -a_*q*dy + d_*dy*dy + c_*dy*r;
        detz = a_*(-dx*r - dz*q) - b_*dy*r + d_*dy*dz;
    }
    else
    {
        q = l.p1.x*dz - l.p1.z*dx;
        r = l.p1.y*dz - l.p1.z*dy;
        det = a_*dx*dz + b_*dz*dy + c_*dz*dz;
        detx = d_*dz*dx - b_*(-q*dy + r*dx) + c_*q*dz;
        dety = a_*(-q*dy + r*dx) + d_*dz*dy + c_*dz*r;
        detz = -a_*dz*q - b_*dz*r + d_*dz*dz;
    }

    if (det <= -0.0001 || det >= 0.0001)
    {
        point<T> tmp {detx / det, dety / det, detz / det};
        if (this->isbelong(tmp))
        {
            return true;
        }
    }
    else
    {
        float distance = a_*l.p1.x + b_*l.p1.y + c_*l.p1.z - d_;
        if (distance > -0.0001 && distance < 0.0001 && 
            (l.line_intersection_plane({array[0], array[1]}) ||
            l.line_intersection_plane({array[1], array[2]}) ||
            l.line_intersection_plane({array[2], array[0]})))
        {
            return true;
        }
    }

    return false;
}

template <typename T>
bool triangle<T>:: triangles_intersection(const triangle<T>& tr) const
{
    if (this->triangle_line_intersection({tr.array[0], tr.array[1]}) ||
        this->triangle_line_intersection({tr.array[1], tr.array[2]}) ||
        this->triangle_line_intersection({tr.array[2], tr.array[0]}))
    {
        return true;
    }
    
    return false;
}

template <typename T>
bool line<T>:: line_intersection_plane(const line<T>& l) const
{
    float ldx = l.p2.x - l.p1.x, ldy = l.p2.y - l.p1.y, ldz = l.p2.z - l.p1.z;
    float dx = p2.x - p1.x, dy = p2.y - p1.y, dz = p2.z - p1.z;
    float p = l.p1.x - p1.x, q = l.p1.y - p1.y;
    float det = -dx*ldy + dy*ldx;
    float dett = -p*ldy + q*ldx, dets = dx*q - dy*p;
    if (det <= -0.0001 || det >= 0.0001)
    {
        float t = dett / det, s = dets / det;
        float z = t*dz + p1.z - s*ldz - l.p1.z;
        if (z > -0.0001 && z < 0.0001 && t >= 0 && t <= 1 && s >= 0 && s <= 1)
        { 
            return true;
        }
    }
    else
    {
        float ldx1 = l.p1.x - p1.x, ldy1 = l.p1.y - p1.y, ldz1 = l.p1.z - p1.z;
        float ldx2 = l.p1.x - p2.x, ldy2 = l.p1.y - p2.y, ldz2 = l.p1.z - p2.z;
        float ldx3 = l.p2.x - p1.x, ldy3 = l.p2.y - p1.y, ldz3 = l.p2.z - p1.z;
        float ldx4 = l.p2.x - p2.x, ldy4 = l.p2.y - p2.y, ldz4 = l.p2.z - p2.z;
        float a = ldy1*ldz2 - ldz1*ldy2, b = ldz1*ldx2 - ldx1*ldz2, c = ldx1*ldy2 - ldy1*ldx2;
        if (a > -0.0001 && a < 0.0001 && b > -0.0001 && b < 0.0001 && c > -0.0001 && c < 0.0001)
        {
            float s = std::sqrt(dx*dx + dy*dy + dz*dz);
            float s1 = std::sqrt(ldx1*ldx1 + ldy1*ldy1 + ldz1*ldz1);
            float s2 = std::sqrt(ldx2*ldx2 + ldy2*ldy2 + ldz2*ldz2);
            float s3 = std::sqrt(ldx3*ldx3 + ldy3*ldy3 + ldz3*ldz3);
            float s4 = std::sqrt(ldx4*ldx4 + ldy4*ldy4 + ldz4*ldz4);
            float tmp1 = s - s1 - s2, tmp2 = s - s3 - s4;
            if ((tmp1 > -0.0001 && tmp1 < 0.0001) || (tmp2 > -0.0001 && tmp2 < 0.0001))
            {
                return true;
            }
        }
    }

    return false;
}