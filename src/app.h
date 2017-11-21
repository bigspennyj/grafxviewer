#ifndef APP_H
#define APP_H

#include <memory>
#include "io.h"

class App {
private:
    std::unique_ptr<SDL_IO> io;
    bool run;
    bool rotate;

public:
    App();

    static constexpr double FRAME_RATE = 60.0;

    int execute();
};

#endif
