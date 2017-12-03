#include "app.h"
#include "appcomponent.h"
#include "modelview.h"
#include "model.h"
#include <cstdint>
#include <iostream>

App::App() :
    io(new SDL_IO(1024, 768)),
    run(true), rotateX(false), rotateY(false), rotateZ(false), model(), showFileDialog(false)
{
}

App::App(std::string pointFile, std::string lineFile) :
    io(new SDL_IO(1024, 768)),
    run(true), rotateX(false), rotateY(false), rotateZ(false), model(pointFile, lineFile), showFileDialog(false)
{
}

std::unique_ptr<MenuComponent> App::createAppMenu()
{
    io->loadImage("./assets/bg5.png", "menu-bg");
    io->loadImage("./assets/left-up.png", "button-up");
    io->loadImage("./assets/left-down.png", "button-down");
    auto menu = io->createMenuComponent(0, 688, 1024, 80);

    auto button = io->createButton(20, 20, 40, 40);
    button->setClickHandler([this](auto& e) 
        { 
            this->model.rotateModel(6, {1, 0, 0});
        });
    menu->addChild(std::move(button));

    auto button2 = io->createButton(80, 20, 40, 40);
    button2->setClickHandler([this](auto& e) 
        { 
            this->model.rotateModel(6, {0, 1, 0});
        });
    menu->addChild(std::move(button2));

    auto button3 = io->createButton(140, 20, 40, 40);
    button3->setClickHandler([this](auto& e) 
        { 
            this->model.rotateModel(6, {0, 0, 1});
        });
    menu->addChild(std::move(button3));

    auto button4 = io->createButton(200, 20, 40, 40);
    button4->setClickHandler([this](auto& e)
        {
            double inUnits = 75.0 / 20.0; //75 pixels in units
            Vector3D<double> translation{ -inUnits, 0, 0, 0 };
            this->model.translateModel(translation);
        });
    menu->addChild(std::move(button4));

    auto button5 = io->createButton(260, 20, 40, 40);
    button5->setClickHandler([this](auto& e)
        {
            double inUnits = 75.0 / 20.0; //75 pixels in units
            Vector3D<double> translation{ inUnits, 0, 0, 0 };
            this->model.translateModel(translation);
        });
    menu->addChild(std::move(button5));

    auto button6 = io->createButton(320, 20, 40, 40);
    button6->setClickHandler([this](auto& e)
        {
            double inUnits = 35.0 / 20.0; //35 pixels in units
            Vector3D<double> translation{ 0, -inUnits, 0, 0 };
            this->model.translateModel(translation);
        });
    menu->addChild(std::move(button6));

    auto button7 = io->createButton(380, 20, 40, 40);
    button7->setClickHandler([this](auto& e)
        {
            double inUnits = 35.0 / 20.0; //75 pixels in units
            Vector3D<double> translation{ 0, inUnits, 0, 0 };
            this->model.translateModel(translation);
        });
    menu->addChild(std::move(button7));

    auto button8 = io->createButton(440, 20, 40, 40);
    button8->setClickHandler([this](auto& e)
        {
            double scaleFactor = 1.1;
            this->model.scaleModel(scaleFactor);
        });
    menu->addChild(std::move(button8));

    auto button9 = io->createButton(500, 20, 40, 40);
    button9->setClickHandler([this](auto& e)
        {
            double scaleFactor = 0.9;
            this->model.scaleModel(scaleFactor);
        });
    menu->addChild(std::move(button9));

    auto button10 = io->createButton(560, 20, 40, 40);
    button10->setClickHandler([this](auto& e)
        {
            std::cout << "toggling file dialog" << std::endl;
            this->showFileDialog = !this->showFileDialog;
        });
    menu->addChild(std::move(button10));
    return menu;
}

int App::execute()
{
    Uint32 delayTime = (1.0 / FRAME_RATE) * 1000;

    auto modelView = io->createModelView(0, 0, 1024, 688, 20, model);
    auto menu = createAppMenu();

    const auto& modelViewRef = io->getRoot()->addChild(std::move(modelView));
    io->getRoot()->addChild(std::move(menu));

    //testing file dialog code
    auto fileSelector = io->createFileSelector((1024 / 2) - 200, (768 / 2) - 250, 400, 500); 
    fileSelector->setOnCloseCallback([&](auto& points, auto& lines)
        {
            std::cout << "points: " << points << "lines: " << lines << std::endl;
            this->showFileDialog = false;
        });
    auto& fileSelectorRef = io->getRoot()->addChild(std::move(fileSelector));

    // menu and button are invalid
    while (run) {
        Uint32 startTicks = io->getTicks();

        run = io->handleEvents();

        if (showFileDialog) {
            fileSelectorRef->setVisible(true);
        } else {
            fileSelectorRef->setVisible(false);
            modelViewRef->invalidate();
        }

        if (rotateX) {
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
