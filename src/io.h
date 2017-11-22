#ifndef IO_H
#define IO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>
#include <cstdint>
#include <vector>
#include <memory>
#include <functional>
#include <iostream>

#include "model.h"

class SDLBaseIO {
public:
    SDLBaseIO() : isInitialized(false)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("Failed to init sdl");
        }
        isInitialized = true;
    }

    virtual ~SDLBaseIO()
    {
        std::cout << "~SDLBaseIO" << std::endl;
        SDL_Quit();
    }
protected:
    bool isInitialized;
};

class Component;
class ComponentContainer;
class MenuComponent;
class Button;
class ModelView;

class SDL_IO: public SDLBaseIO {
public:
    struct EventArgs {
        int x, y;
        bool buttonDown;
    };
    template<typename T>
    using DeletedPointer = std::unique_ptr<T, std::function<void(T*)>>;

    using WindowPointer = DeletedPointer<SDL_Window>;
    using RendererPointer = DeletedPointer<SDL_Renderer>;
    using TexturePointer = DeletedPointer<SDL_Texture>;
    using SurfacePointer = DeletedPointer<SDL_Surface>;

    using SurfacePointerBorrow = const SurfacePointer&;

    SDL_IO(int width, int height);
    virtual ~SDL_IO();

    void loadImage(std::string imgPath, std::string imgKey);
    RendererPointer createSoftwareRenderer(const Component& c);
    RendererPointer createSoftwareRenderer(const std::unique_ptr<Component>& c);
    RendererPointer createSoftwareRenderer();
    void renderImage(std::string key, int x, int y);
    void renderImage(const SurfacePointer& p, std::string key, int x, int y);
    void updateScreen();

    void drawRectangle(int x1, int y1, int x2, int y2);
    void drawRectangle(const RendererPointer& r, int x1, int y1, int x2, int y2);
    void drawRectangle(SurfacePointerBorrow s, int x1, int y1, int x2, int y2);
    void drawComponent(const Component& c);
    void drawComponent(const RendererPointer& r, const Component& c);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawLine(const RendererPointer& r, int x1, int y1, int x2, int y2);
    //void drawLines(std::vector<Vector3D> points);
    void setColor(unsigned int rgba);
    void setColor(const RendererPointer& rp, int r, int g, int b, int a);

    const std::unique_ptr<ComponentContainer>& getRoot()
    {
        return rootComponent;
    }

    bool handleEvents();

    void setWidth(int w) noexcept;
    void setHeight(int h) noexcept;
    int getWidth() const noexcept;
    int getHeight() const noexcept;

    void doDelay(Uint32 ms);
    Uint32 getTicks();

    std::unique_ptr<MenuComponent> createMenuComponent(int x, int y, int width, int height);
    std::unique_ptr<Button> createButton(int x, int y, int width, int height);
    std::unique_ptr<ModelView> createModelView(int x, int y, int width, int height, Model& m);

private:
    WindowPointer window;
    RendererPointer renderer;
    TexturePointer screenTexture;
    SurfacePointer buffer;

    std::unique_ptr<ComponentContainer> rootComponent;

    std::map<std::string, SDL_Surface *> texMap;

    int screenWidth;
    int screenHeight;
    Uint32 currentDrawColor;

    std::vector<std::pair<SDL_Point, SDL_Point>> lineSegments;

    void CycleTexture();
};

#endif //IO_H
