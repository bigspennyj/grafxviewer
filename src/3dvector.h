#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <array>

class Vector3D {
public:
    Vector3D() = default;

    Vector3D(double x, double y, double z) :
        terms{{x, y, z, 1}}
    {}

    double operator[](int i) { return terms[i]; }

    double getX() const noexcept { return terms[0]; }
    double getY() const noexcept { return terms[1]; }
    double getZ() const noexcept { return terms[2]; }
    double getH() const noexcept { return terms[3]; }

    void setX(double x) noexcept { terms[0] = x; }
    void setY(double y) noexcept { terms[1] = y; }
    void setZ(double z) noexcept { terms[2] = z; }
    void setH(double h) noexcept { terms[3] = h; }

private:
    std::array<double, 4> terms;
};

#endif // VECTOR3D_H
