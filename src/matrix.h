#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include "3dvector.h"

class TransformationMatrix;

class Matrix {
public:
    Matrix() = default;

    Matrix(int n) : rows(n) {}

    Matrix(std::vector<Vector3D>& r) : rows(r) {}
    Matrix(std::initializer_list<Vector3D> r) : rows(r) {}

    virtual void addRow(Vector3D&& row);

    Vector3D& operator[](int i);

    const Vector3D& operator[](int i) const;

    Matrix& operator*=(const TransformationMatrix& rhs);
    bool operator==(const Matrix& other);

    auto& getRows() const noexcept { return rows; }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

protected:

    std::vector<Vector3D> rows;

};

class TransformationMatrix : public Matrix {
public:
    TransformationMatrix() : Matrix(4)
    {
        for (int i = 0; i < 4; i++)
            rows[i][i] = 1;
    }

    TransformationMatrix(std::initializer_list<Vector3D> r) : Matrix(r)
    {
    }
    virtual void addRow(Vector3D&& row) override 
    {
        throw std::runtime_error("Can't add row to tranformation matrix");
    }

    void addTranslation(double x, double y, double z);
    void addRotation(const Vector3D& vec);
};

#endif // MATRIX_H
