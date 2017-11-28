#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <array>

template<typename U>
struct TransformationMatrix;

template<typename T>
struct Vector3D {
    T x, y, z, h;

    T& operator[](int i) {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return h;
        default:
            throw std::runtime_error("invalid index given to vector");
        }
    }

    T operator[](int i) const {
        switch (i) {
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return h;
        default:
            throw std::runtime_error("invalid index given to vector");
        }
    }

    template<typename Scalar>
    Vector3D& operator*=(Scalar scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    template<typename Scalar>
    Vector3D operator*(Scalar scalar)
    {
        Vector3D result(*this);
        result *= scalar;
        return result;
    }

    template<typename U>
    Vector3D operator*(const TransformationMatrix<U>& matrix)
    {
        Vector3D result(*this);
        result *= matrix;
        return result;
    }

    template<typename U>
    Vector3D& operator*=(const TransformationMatrix<U>& matrix)
    {
        std::array<T, 4> newTerms;
        for (int i = 0; i < 4; i++) {
            T newTerm = 0;
            for (int j = 0; j < 4; j++) {
                newTerm += (*this)[j] * matrix[j][i];
            }
            newTerms[i] = newTerm;
        }
        x = newTerms[0];
        y = newTerms[1];
        z = newTerms[2];
        h = newTerms[3];

        return *this;
    }

    template<typename U>
    T operator*(const Vector3D<U>& rhs)
    {
        T result = (x * rhs.x) + (y * rhs.y) + (z * rhs.z);
        return result;
    }

    template<typename U>
    Vector3D& operator+=(const Vector3D<U>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    template<typename U>
    Vector3D operator+(const Vector3D<U>& rhs)
    {
        Vector3D result(*this);
        result += rhs;
        return result;
    }

};

#endif // VECTOR3D_H
