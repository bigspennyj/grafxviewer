#include "app.h"
#include "component.h"
#include <cstdint>
#include <iostream>

App::App() :
    io(new SDL_IO(640, 480)),
    run(true),
    leftBackground(0xffffffff)
{
    io->attach(*this);
}

void App::notify()
{
    leftBackground = ~leftBackground;
}

int App::execute()
{
    Uint32 delayTime = (1.0 / FRAME_RATE) * 1000;
    auto menu = io->createMenuComponent(0, 380, 640, 100);

    while (run) {
        Uint32 startTicks = io->getTicks();
        run = io->handleEvents();

        int thisHeight = io->getHeight();

        io->setColor(leftBackground);
        io->drawRectangle(0, 0, 0, thisHeight);

        io->setColor(0xff666666);

        menu->update();
        io->updateScreen();

        Uint32 ticksElapsed = io->getTicks() - startTicks;
        if (ticksElapsed < delayTime) {
            io->doDelay((int)(delayTime - ticksElapsed));
        }
    }

    return 0;
}
