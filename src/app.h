#ifndef APP_H
#define APP_H

#include <memory>
#include "io.h"

class App : public Observer<SDL_IO> {
private:
    std::unique_ptr<SDL_IO> io;
    bool run;
    int leftBackground;

public:
    App();

    static constexpr double FRAME_RATE = 60.0;

    int execute();
    void notify() override;
};

#endif
