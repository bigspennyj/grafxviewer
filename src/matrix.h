#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <array>
#include "3dvector.h"

#define PI 3.14159265

template<typename T>
struct TransformationMatrix {
    std::array<std::array<T, 4>, 4> matrix;
    
    std::array<T, 4> operator[](int i) const
    {
        return matrix[i];
    }

    std::array<T, 4>& operator[](int i)
    {
        return matrix[i];
    }

    template<typename U>
    bool operator==(const TransformationMatrix<U>& other)
    {
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < 4; j++) {
                if (matrix[i][j] != other.matrix[i][j])
                    return false;
            }
        }
        return true;
    }

    template<typename U>
    TransformationMatrix operator*(const TransformationMatrix<U>& rhs)
    {
        TransformationMatrix result(*this);
        result *= rhs;
        return result;
    }

    template<typename U>
    TransformationMatrix& operator*=(const TransformationMatrix<U>& rhs)
    {
        for (auto& row : matrix) {
            std::array<T, 4> newRow;
            for (int i = 0; i < 4; i++) {
                double newTerm = 0;
                for (int j = 0; j < 4; j++) {
                    newTerm += row[j] * rhs[j][i];
                }
                newRow[i] = newTerm;
            }
            row = newRow;
        }

        return *this;
    }

    static TransformationMatrix RotationMatrix(double degrees, const Vector3D<double>& axis)
    {
        double rads = PI * degrees / 180.0;
        double sinTheta = sin(rads);
        double cosTheta = cos(rads);

        if (axis.x == 1.0) {
            std::array<std::array<T, 4>, 4> points{{
                {{1, 0, 0, 0}},
                {{0, cosTheta, -sinTheta, 0}},
                {{0, sinTheta, cosTheta, 0}},
                {{0, 0, 0, 1}}
            }};
            return TransformationMatrix(points);
        } else if (axis.y == 1.0) {
            std::array<std::array<T, 4>, 4> points{{
                {{cosTheta, 0, -sinTheta, 0}},
                {{0, 1, 0, 0}},
                {{sinTheta, 0, cosTheta, 0}},
                {{0, 0, 0, 1}}
            }};
            return TransformationMatrix(points);
        } else if (axis.z == 1.0) {
            std::array<std::array<T, 4>, 4> points{{
                {{cosTheta, sinTheta, 0, 0}},
                {{-sinTheta, cosTheta, 0, 0}},
                {{0, 0, 1, 0}},
                {{0, 0, 0, 1}}
            }};
            return TransformationMatrix(points);
        } else {
            throw std::runtime_error("invalid rotation axis");
        }
    }

    static TransformationMatrix ScaleMatrix(double factor, const Vector3D<double>& axis)
    {
        if (axis.x == 1.0) {
            std::array<std::array<T, 4>, 4> points{{
                {{factor, 0, 0, 0}},
                {{0, 1, 0, 0}},
                {{0, 0, 1, 0}},
                {{0, 0, 0, 1}}
            }};
            return TransformationMatrix(points);
        } else if (axis.y == 1.0) {
            std::array<std::array<T, 4>, 4> points{{
                {{1, 0, 0, 0}},
                {{0, factor, 0, 0}},
                {{0, 0, 1, 0}},
                {{0, 0, 0, 1}}
            }};
            return TransformationMatrix(points);
        } else if (axis.z == 1.0) {
            std::array<std::array<T, 4>, 4> points{{
                {{1, 0, 0, 0}},
                {{0, 1, 0, 0}},
                {{0, 0, factor, 0}},
                {{0, 0, 0, 1}}
            }};
            return TransformationMatrix(points);
        } else {
            throw std::runtime_error("invalid scale axis");
        }
    }

    static TransformationMatrix ScaleMatrix(double factor)
    {
        std::array<std::array<T, 4>, 4> points{{
            {{factor, 0, 0, 0}},
            {{0, factor, 0, 0}},
            {{0, 0, factor, 0}},
            {{0, 0, 0, 1}}
        }};
        return TransformationMatrix(points);
    }

    TransformationMatrix(std::array<std::array<T, 4>, 4> m) : matrix(m) {}

    static TransformationMatrix TranslationMatrix(const Vector3D<double>& transformation)
    {
        std::array<std::array<T, 4>, 4> m{{
            {{1, 0, 0, 0}},
            {{0, 1, 0, 0}},
            {{0, 0, 1, 0}},
            {{transformation.x, transformation.y, transformation.z, 1}}
        }};

        return TransformationMatrix(m);
    }

    //static TransformationMatrix SkewMatrix(double factor, const Vector3D<double>& axis)
};
#endif // MATRIX_H
