#include "appcomponent.h"
#include "modelview.h"

void MenuComponent::redraw(const DrawingContext& c)
{
    //draw bg
    c.setColor(0x18, 0x13, 0x1B, 0xff);
    c.drawRectangle(0, 0, width, height);
    c.drawImage("menu-bg", 0, 0);
    c.drawComponent(*this);
    needUpdate = false;
}

void Button::redraw(const DrawingContext& c)
{
    c.drawImage("button-up", 0, 0);
    c.drawComponent(*this);
    needUpdate = false;
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
