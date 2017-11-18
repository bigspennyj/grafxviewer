#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include "3dvector.h"

class TransformationMatrix;

class Matrix {
public:
    Matrix() = default;

    Matrix(int n) : rows(n) {}

    virtual void addRow(Vector3D&& row);

    Vector3D& operator[](int i);

    const Vector3D& operator[](int i) const;

    Matrix& operator*=(const TransformationMatrix& rhs);
    bool operator==(const Matrix& other);

    auto& getRows() const noexcept { return rows; }

protected:

    std::vector<Vector3D> rows;

};

class TransformationMatrix : public Matrix {
public:
    TransformationMatrix() : Matrix(4)
    {
        rows.emplace_back(1, 0, 0, 0);
        rows.emplace_back(0, 1, 0, 0);
        rows.emplace_back(0, 0, 1, 0);
        rows.emplace_back(0, 0, 0, 1);
    }

    virtual void addRow(Vector3D&& row) override 
    {
        throw std::runtime_error("Can't add row to tranformation matrix");
    }

};

#endif // MATRIX_H
