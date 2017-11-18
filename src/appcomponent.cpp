#include "appcomponent.h"
#include "modelview.h"

void MenuComponent::redraw(const DrawingContext& c)
{
    c.setColor(0xff666666);
    c.drawRectangle(surface, 0, 0, width, height);
    c.drawComponent(*this);
}

void Button::redraw(const DrawingContext& c)
{
    c.setColor(currentColor);
    c.drawRectangle(surface, 0, 0, width, height);
    c.drawComponent(*this);
}

bool Button::handleEvent(const SDL_IO::EventArgs& e)
{
    bool ourEvent = AABB(e.x, e.y);
    if (ourEvent && !isPressed) {
        //handle - we just got clicked
        cycleColor();
        isPressed = true;
        if (onClickCallback) {
            onClickCallback(e);
        }
    }

    // always update if we're pressed and the button comes up
    if (!e.buttonDown && isPressed) {
        cycleColor();
        isPressed = false;
    }
    return ourEvent;
}

void Button::cycleColor() noexcept
{
    currentColor = (~currentColor) | 0xff000000;
    needUpdate = true;
}
