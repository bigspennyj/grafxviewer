#ifndef APP_H
#define APP_H

#include <memory>
#include "io.h"

class App {
private:
    std::unique_ptr<SDL_IO> io;
    bool run;
    bool rotateX, rotateY, rotateZ;
    Model model;

    void initUIComponents();
    std::unique_ptr<MenuComponent> createAppMenu();

public:
    App();
    App(std::string pointfile, std::string linefile);

    static constexpr double FRAME_RATE = 60.0;

    int execute();
};

#endif
