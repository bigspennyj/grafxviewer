#include "app.h"
#include "appcomponent.h"
#include "modelview.h"
#include "model.h"
#include <cstdint>
#include <iostream>

App::App() :
    io(new SDL_IO(1024, 768)),
    run(true), rotate(false), model()
{
}

App::App(std::string pointFile, std::string lineFile) :
    io(new SDL_IO(1024, 768)),
    run(true), rotate(false), model(pointFile, lineFile)
{
}

void App::initUIComponents()
{
    io->loadImage("./assets/bg5.png", "menu-bg");
    io->loadImage("./assets/button.png", "button-up");
    auto menu = io->createMenuComponent(0, 688, 1024, 80);

    auto button = io->createButton(20, 20, 40, 40);
    button->setClickHandler([this](auto& e) 
        { 
            std::cout << "from the click handler!  got " << e.x << " " << e.y << std::endl; 
            this->rotate = !this->rotate;
        });
    menu->addChild(std::move(button));

    auto modelView = io->createModelView(0, 0, 1024, 688, model);

    io->getRoot()->addChild(std::move(modelView));
    io->getRoot()->addChild(std::move(menu));
}

int App::execute()
{
    Uint32 delayTime = (1.0 / FRAME_RATE) * 1000;

    initUIComponents();

    TransformationMatrix rotation = {
        {0.9986, 0, 0.0523, 0},
        {0, 1, 0, 0},
        {-0.0523, 0, 0.9986, 0},
        {0, 0, 0, 1}
    };
    // menu and button are invalid
    while (run) {
        Uint32 startTicks = io->getTicks();

        run = io->handleEvents();

        if (rotate) {
            model.applyTransformation(rotation);
        }

        io->updateScreen();

        Uint32 ticksElapsed = io->getTicks() - startTicks;
        if (ticksElapsed < delayTime) {
            io->doDelay((int)(delayTime - ticksElapsed));
        }
    }

    return 0;
}
