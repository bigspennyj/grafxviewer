#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

#include "3dvector.h"
#include "matrix.h"

class Model {
public:
    Model() = default;

    Model(std::string pf, std::string lf) : originalCenter(), currentCenter(), currentCoords(), originalCoords()
    {
        std::string line;
        std::ifstream pointFile(pf);
        std::ifstream lineFile(lf);

        double cx, cy, cz;
        pointFile >> cx >> cy >> cz;

        if (pointFile) {
            originalCenter = {cx, cy, cz, 1};
            currentCenter = {cx, cy, cz, 1};
            double x, y, z;
            while (pointFile >> x >> y >> z) {
                originalCoords.push_back({x, y, z, 1});
            }
            currentCoords = originalCoords;

            if (lineFile) {
                int l1, l2;
                while (lineFile >> l1 >> l2) {
                    lineSegments.push_back(std::make_pair(l1, l2));
                }
            } else {
                std::cerr << "error reading line file " << lf << ", skipping..." << std::endl;
            }
        } else {
            std::cerr << "error reading pointFile " << pf << ", skipping..." << std::endl;
        }
    }

    //const Matrix& getOriginalCoords() const noexcept { return originalCoords; }
    std::vector<Vector3D<double>>& getCurrentCoords() noexcept { return currentCoords; }
    const std::vector<std::pair<int, int>>& getLineSegments() const noexcept { return lineSegments; }

    Vector3D<double> getOriginalCenter() const noexcept { return originalCenter; }
    Vector3D<double> getCurrentCenter() const noexcept { return currentCenter; }
    
    void rotateModel(double degrees, const Vector3D<double> axis)
    {
        auto initialTransformation = TransformationMatrix<double>::TranslationMatrix(
                    {-currentCenter.x, -currentCenter.y, -currentCenter.z, 1});

        auto returnTranslation = TransformationMatrix<double>::TranslationMatrix(
            {currentCenter.x, currentCenter.y, currentCenter.z, 1});

        auto rotation = TransformationMatrix<double>::RotationMatrix(degrees, axis);

        auto transformation = initialTransformation * rotation * returnTranslation;

        applyTransformation(transformation);
    }

    void translateModel(const Vector3D<double> trans)
    {
        auto transformation = TransformationMatrix<double>::TranslationMatrix(trans);
        applyTransformation(transformation);

        currentCenter *= transformation;
    }

    void scaleModel(double factor, const Vector3D<double> trans)
    {
        auto initialTranslation = TransformationMatrix<double>::TranslationMatrix(
                    {-currentCenter.x, -currentCenter.y, -currentCenter.z, 1});

        auto returnTranslation = TransformationMatrix<double>::TranslationMatrix(
            {currentCenter.x, currentCenter.y, currentCenter.z, 1});

        auto scale = TransformationMatrix<double>::ScaleMatrix(factor, trans);

        auto transformation = initialTranslation * scale * returnTranslation;

        applyTransformation(transformation);
    }

    void scaleModel(double factor)
    {
        auto initialTranslation = TransformationMatrix<double>::TranslationMatrix(
                    {-currentCenter.x, -currentCenter.y, -currentCenter.z, 1});

        auto returnTranslation = TransformationMatrix<double>::TranslationMatrix(
            {currentCenter.x, currentCenter.y, currentCenter.z, 1});

        auto scale = TransformationMatrix<double>::ScaleMatrix(factor);

        auto transformation = initialTranslation * scale * returnTranslation;

        applyTransformation(transformation);
    }

    void skewModelHorrizontally(double factor)
    {
        Vector3D<double> axis = {1, 0, 0, 0};
        auto transformation = TransformationMatrix<double>::SkewMatrix(factor, axis);
        applyTransformation(transformation);
    }

    void skewModelVertically(double factor)
    {
        Vector3D<double> axis = {0, 1, 0, 0};
        auto transformation = TransformationMatrix<double>::SkewMatrix(factor, axis);
        applyTransformation(transformation);
    }

    void applyTransformation(const TransformationMatrix<double> m)
    {
        for (auto& row : currentCoords)
            row *= m;
    }

    void reset()
    {
        currentCoords = originalCoords;
        currentCenter = originalCenter;
    }
private:
    Vector3D<double> originalCenter;
    Vector3D<double> currentCenter;

    std::vector<Vector3D<double>> currentCoords;
    std::vector<Vector3D<double>> originalCoords;
    std::vector<std::pair<int, int>> lineSegments;
};

#endif // model_h
