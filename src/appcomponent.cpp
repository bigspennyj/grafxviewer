#include "appcomponent.h"

void MenuComponent::redraw(const DrawingContext& c)
{
    c.setColor(0xff666666);
    c.drawRectangle(surface, 0, 0, width, height);
    c.drawComponent(*this);
}

void Button::redraw(const DrawingContext& c)
{
    std::cout << "DRAW BUTTON " << currentColor << std::endl;
    c.setColor(currentColor);
    c.drawRectangle(surface, 0, 0, width, height);
    // TODO: move this up to SDL_IO
    c.drawComponent(*this);
}

bool Button::handleEvent(const SDL_IO::EventArgs& e)
{
    if (!e.buttonDown && isPressed) {
        cycleColor();
        isPressed = false;
    }

    if (AABB(e.x, e.y) && !isPressed) {
        //handle
        cycleColor();
        isPressed = true;
        if (onClickCallback) {
            // catch exceptions here?
            onClickCallback(e);
        }
        return true;
    }
    return false;
}

void Button::cycleColor() noexcept
{
    currentColor = (~currentColor) | 0xff000000;
    needUpdate = true;
}
