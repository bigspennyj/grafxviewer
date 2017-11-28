#include "app.h"
#include "appcomponent.h"
#include "modelview.h"
#include "model.h"
#include <cstdint>
#include <iostream>

App::App() :
    io(new SDL_IO(1024, 768)),
    run(true), rotateX(false), rotateY(false), rotateZ(false), model()
{
}

App::App(std::string pointFile, std::string lineFile) :
    io(new SDL_IO(1024, 768)),
    run(true), rotateX(false), rotateY(false), rotateZ(false), model(pointFile, lineFile)
{
}

std::unique_ptr<MenuComponent> App::createAppMenu()
{
    io->loadImage("./assets/bg5.png", "menu-bg");
    io->loadImage("./assets/button.png", "button-up");
    auto menu = io->createMenuComponent(0, 688, 1024, 80);

    auto button = io->createButton(20, 20, 40, 40);
    button->setClickHandler([this](auto& e) 
        { 
            this->rotateX = !this->rotateX;
        });
    menu->addChild(std::move(button));

    auto button2 = io->createButton(80, 20, 40, 40);
    button2->setClickHandler([this](auto& e) 
        { 
            this->rotateY = !this->rotateY;
        });
    menu->addChild(std::move(button2));

    auto button3 = io->createButton(140, 20, 40, 40);
    button3->setClickHandler([this](auto& e) 
        { 
            this->rotateZ = !this->rotateZ;
        });
    menu->addChild(std::move(button3));

    return menu;
}

void App::initUIComponents()
{
    auto modelView = io->createModelView(0, 0, 1024, 688, model);
    auto menu = createAppMenu();

    io->getRoot()->addChild(std::move(modelView));
    io->getRoot()->addChild(std::move(menu));
}

int App::execute()
{
    Uint32 delayTime = (1.0 / FRAME_RATE) * 1000;

    initUIComponents();

    // menu and button are invalid
    while (run) {
        Uint32 startTicks = io->getTicks();

        run = io->handleEvents();

        if (rotateX) {
            model.rotateModel(6, {1, 0, 0});
        }

        if (rotateY) {
            model.rotateModel(6, {0, 1, 0});
        }

        if (rotateZ) {
            model.rotateModel(6, {0, 0, 1});
        }

        io->updateScreen();

        Uint32 ticksElapsed = io->getTicks() - startTicks;
        if (ticksElapsed < delayTime) {
            io->doDelay((int)(delayTime - ticksElapsed));
        }
    }

    return 0;
}
