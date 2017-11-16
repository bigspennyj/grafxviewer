#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include "3dvector.h"

class Matrix {
public:
    Matrix() = default;

    Matrix(int n) : rows(n) {}

    void addRow(Vector3D&& row)
    {
        rows.push_back(row);
    }

    Vector3D& operator[](int i)
    {
        return rows[i];
    }

    const Vector3D& operator[](int i) const
    {
        return rows[i];
    }
    auto& getRows() const noexcept { return rows; }
private:
    std::vector<Vector3D> rows;
};

#endif // MATRIX_H
