#include "app.h"
#include "appcomponent.h"
#include "model.h"
#include <cstdint>
#include <iostream>

App::App() :
    io(new SDL_IO(1024, 768)),
    run(true)
{
}

int App::execute()
{
    Uint32 delayTime = (1.0 / FRAME_RATE) * 1000;
    // temporary initialization section
    // this is dangerous and should be fixed!
    auto menu = io->createMenuComponent(0, 688, 1024, 80);

    auto button = io->createButton(15, 15, 50, 50);
    button->setClickHandler([](auto& e) { std::cout << "from the click handler!  got " << e.x << " " << e.y << std::endl; });
    menu->addChild(std::move(button));

    std::ifstream points("./Qpoints.200810.dat");
    std::ifstream lines("./Qlines.200810.dat");
    Model model(points, lines);

    auto modelView = io->createModelView(0, 0, 1024, 688, model);

    io->getRoot()->addChild(std::move(modelView));
    io->getRoot()->addChild(std::move(menu));
    // menu and button are invalid
    while (run) {
        Uint32 startTicks = io->getTicks();

        run = io->handleEvents();

        io->updateScreen();

        Uint32 ticksElapsed = io->getTicks() - startTicks;
        if (ticksElapsed < delayTime) {
            io->doDelay((int)(delayTime - ticksElapsed));
        }
    }

    return 0;
}
