#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "3dvector.h"
#include "matrix.h"

class Model {
public:
    Model() = default;

    Model(std::ifstream& pointFile, std::ifstream& lineFile) : currentCoords()
    {
        std::string line;
        double cx, cy, cz;
        pointFile >> cx >> cy >> cz;
        if (pointFile) {
            std::cout << "reading pointfile" << std::endl;
            double x, y, z;
            while (pointFile >> x >> y >> z) {
                // TODO: this
                currentCoords.addRow(Vector3D(x - cx, (y - cy) * -1, z - cz));
            }
            std::cout << "read " << currentCoords.getRows().size() << " points" << std::endl;
        }
        pointFile.close();
        if (lineFile) {
            std::cout << "reading linefile" << std::endl;
            int l1, l2;
            while (lineFile >> l1 >> l2) {
                lineSegments.push_back(std::make_pair(l1, l2));
            }
            std::cout << "read " << lineSegments.size() << " segments" << std::endl;
        }
        lineFile.close();
    }

    Model(Matrix c) : currentCoords(c), lineSegments() {}
    //const Matrix& getOriginalCoords() const noexcept { return originalCoords; }
    const Matrix& getCurrentCoords() const noexcept { return currentCoords; }
    const std::vector<std::pair<int, int>>& getLineSegments() const noexcept { return lineSegments; }

    void applyTransformation(TransformationMatrix& m)
    {
        currentCoords *= m;
    }
private:
    //Matrix originalCoords;
    Matrix currentCoords;
    std::vector<std::pair<int, int>> lineSegments;
};

#endif // model_h
