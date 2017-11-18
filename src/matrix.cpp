#include "matrix.h"


void Matrix::addRow(Vector3D&& row)
{
    rows.push_back(row);
}

Vector3D& Matrix::operator[](int i)
{
    return rows[i];
}

const Vector3D& Matrix::operator[](int i) const
{
    return rows[i];
}

bool Matrix::operator==(const Matrix& other)
{
    if (rows.size() != other.rows.size())
        return false;

    for (int i = 0; i < rows.size(); i++) {
        for (int j = 0; j < 4; j++) {
            if (rows[i][j] != other.rows[i][j])
                return false;
        }
    }
    return true;
}


Matrix& Matrix::operator*=(const TransformationMatrix& rhs)
{
    std::vector<Vector3D> newRows(rows.size());
    
    for (auto& row : rows) {
        Vector3D newRow;
        for (int i = 0; i < 4; i++) {
            double newTerm = 0;
            for (int j = 0; j < 4; j++) {
                newTerm += row[j] * rhs[i][j];
            }
            newRow[i] = newTerm;
        }
        newRows.push_back(newRow);
    }

    rows = newRows;
    return *this;
}
