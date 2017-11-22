#include <iostream>
#include <memory>
#include "app.h"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "filenames expected" << std::endl;
        return -2;
    }
    std::unique_ptr<App> app;
    try {
        app.reset(new App(argv[1], argv[2]));
    } catch (std::runtime_error e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    int returnCode = 0;
    try {
        returnCode = app->execute();
    } catch (std::runtime_error ee) {
        std::cout << "Application error: " << ee.what() << std::endl;
        return -1;
    }
    return returnCode;
}
