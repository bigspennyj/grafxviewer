#ifndef MODEL_VIEW_H
#define MODEL_VIEW_H

#include "component.h"
#include "model.h"
#include "matrix.h"

class ModelView : public Component {
public:
    ModelView(int x_, int y_, int width_, int height_, int unit_, Model& model_,
            SDL_IO::TexturePointer tex)
        : Component(x_, y_, width_, height_, std::move(tex)),
        model(model_), unit(unit_)
    {}

    virtual void redraw(const DrawingContext& c) override;
    virtual bool handleEvent(const SDL_IO::EventArgs& e) override { return false; }

private:
    Model& model;
    double unit;

    TransformationMatrix<double> computeProjectionMatrix();
};

#endif // MODEL_VIEW_H
