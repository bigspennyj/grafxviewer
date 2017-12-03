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
    // this is all really ugly.
    io->loadImage("./assets/bg5.png", "menu-bg");
    io->loadImage("./assets/left-up.png", "button-up");
    io->loadImage("./assets/left-down.png", "button-down");
    auto menu = io->createMenuComponent(0, 688, 1024, 80);

    io->loadImage("./assets/rotx-up.png", "rotx-up");
    io->loadImage("./assets/rotx-down.png", "rotx-down");
    auto button = io->createButton(20, 20, 40, 40, "rotx");
    button->setClickHandler([this](auto& e) 
    { 
        this->model.rotateModel(6, {1, 0, 0});
    });
    menu->addChild(std::move(button));

    io->loadImage("./assets/roty-up.png", "roty-up");
    io->loadImage("./assets/roty-down.png", "roty-down");
    auto button2 = io->createButton(80, 20, 40, 40, "roty");
    button2->setClickHandler([this](auto& e) 
    { 
        this->model.rotateModel(6, {0, 1, 0});
    });
    menu->addChild(std::move(button2));

    io->loadImage("./assets/rotz-up.png", "rotz-up");
    io->loadImage("./assets/rotz-down.png", "rotz-down");
    auto button3 = io->createButton(140, 20, 40, 40, "rotz");
    button3->setClickHandler([this](auto& e) 
    { 
        this->model.rotateModel(6, {0, 0, 1});
    });
    menu->addChild(std::move(button3));

    io->loadImage("./assets/left-up.png", "left-up");
    io->loadImage("./assets/left-down.png", "left-down");
    auto button4 = io->createButton(200, 20, 40, 40, "left");
    button4->setClickHandler([this](auto& e)
    {
        double inUnits = 75.0 / 20.0; //75 pixels in units
        Vector3D<double> translation{ -inUnits, 0, 0, 0 };
        this->model.translateModel(translation);
    });
    menu->addChild(std::move(button4));

    io->loadImage("./assets/right-up.png", "right-up");
    io->loadImage("./assets/right-down.png", "right-down");
    auto button5 = io->createButton(260, 20, 40, 40, "right");
    button5->setClickHandler([this](auto& e)
    {
        double inUnits = 75.0 / 20.0; //75 pixels in units
        Vector3D<double> translation{ inUnits, 0, 0, 0 };
        this->model.translateModel(translation);
    });
    menu->addChild(std::move(button5));

    io->loadImage("./assets/down-up.png", "down-up");
    io->loadImage("./assets/down-down.png", "down-down");
    auto button6 = io->createButton(320, 20, 40, 40, "down");
    button6->setClickHandler([this](auto& e)
    {
        double inUnits = 35.0 / 20.0; //35 pixels in units
        Vector3D<double> translation{ 0, -inUnits, 0, 0 };
        this->model.translateModel(translation);
    });
    menu->addChild(std::move(button6));

    io->loadImage("./assets/up-up.png", "up-up");
    io->loadImage("./assets/up-down.png", "up-down");
    auto button7 = io->createButton(380, 20, 40, 40, "up");
    button7->setClickHandler([this](auto& e)
    {
        double inUnits = 35.0 / 20.0; //75 pixels in units
        Vector3D<double> translation{ 0, inUnits, 0, 0 };
        this->model.translateModel(translation);
    });
    menu->addChild(std::move(button7));

    io->loadImage("./assets/scaleup-up.png", "scaleup-up");
    io->loadImage("./assets/scaleup-down.png", "scaleup-down");
    auto button8 = io->createButton(440, 20, 40, 40, "scaleup");
    button8->setClickHandler([this](auto& e)
        {
            double scaleFactor = 1.1;
            this->model.scaleModel(scaleFactor);
        });
    menu->addChild(std::move(button8));

    io->loadImage("./assets/scaledown-up.png", "scaledown-up");
    io->loadImage("./assets/scaledown-down.png", "scaledown-down");
    auto button9 = io->createButton(500, 20, 40, 40, "scaledown");
    button9->setClickHandler([this](auto& e)
    {
        double scaleFactor = 0.9;
        this->model.scaleModel(scaleFactor);
    });
    menu->addChild(std::move(button9));

    io->loadImage("./assets/skewh-up.png", "skewh-up");
    io->loadImage("./assets/skewh-down.png", "skewh-down");
    auto button10 = io->createButton(560, 20, 40, 40, "skewh");
    button10->setClickHandler([this](auto& e)
    {
        double skewFactor = 0.1;
        this->model.skewModelHorrizontally(skewFactor);
    });
    menu->addChild(std::move(button10));

    io->loadImage("./assets/skewv-up.png", "skewv-up");
    io->loadImage("./assets/skewv-down.png", "skewv-down");
    auto button11 = io->createButton(620, 20, 40, 40, "skewv");
    button11->setClickHandler([this](auto& e)
    {
        double skewFactor = 0.1;
        this->model.skewModelVertically(skewFactor);
    });
    menu->addChild(std::move(button11));

    io->loadImage("./assets/crotx-up.png", "crotx-up");
    io->loadImage("./assets/crotx-down.png", "crotx-down");
    auto button12 = io->createButton(680, 20, 40, 40, "crotx");
    button12->setClickHandler([this](auto& e)
    {
        this->rotateX = !this->rotateX;
    });
    menu->addChild(std::move(button12));

    io->loadImage("./assets/croty-up.png", "croty-up");
    io->loadImage("./assets/croty-down.png", "croty-down");
    auto button13 = io->createButton(740, 20, 40, 40, "croty");
    button13->setClickHandler([this](auto& e)
    {
        this->rotateY = !this->rotateY;
    });
    menu->addChild(std::move(button13));

    io->loadImage("./assets/crotz-up.png", "crotz-up");
    io->loadImage("./assets/crotz-down.png", "crotz-down");
    auto button14 = io->createButton(800, 20, 40, 40, "crotz");
    button14->setClickHandler([this](auto& e)
    {
        this->rotateZ = !this->rotateZ;
    });
    menu->addChild(std::move(button14));

    io->loadImage("./assets/reset-up.png", "reset-up");
    io->loadImage("./assets/reset-down.png", "reset-down");
    auto button15 = io->createButton(860, 20, 40, 40, "reset");
    button15->setClickHandler([this](auto& e)
    {
        this->model.reset();
    });
    menu->addChild(std::move(button15));
    return menu;
}

void App::initUIComponents()
{
    auto modelView = io->createModelView(0, 0, 1024, 688, 20, model);
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
