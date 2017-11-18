#include "io.h"
#include "component.h"
#include "appcomponent.h"
#include <iostream>

SDL_IO::SDL_IO(int width, int height)
    : SDLBaseIO(),
      window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer),
      screenTexture(nullptr, SDL_DestroyTexture),
      buffer(nullptr, SDL_FreeSurface),
      rootComponent(new ComponentContainer(0, 0, width, height, nullptr)),
      texMap(),
      screenWidth(width),
      screenHeight(height),
      currentDrawColor(0)
{
    window.reset(SDL_CreateWindow("a thing",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            screenWidth, screenHeight, 0));

    if (!window) {
        throw std::runtime_error("Failed to create a window");
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) == imgFlags) {
        renderer.reset(SDL_CreateRenderer(window.get(), -1, 0));
        screenTexture.reset(SDL_CreateTexture(renderer.get(),
                        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                        width, height));
        buffer.reset(SDL_CreateRGBSurface(0, width, height, 32,
                0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000));
        SDL_FillRect(buffer.get(), nullptr, 0xffffffff);
        SDL_SetRenderDrawColor(renderer.get(), 0xff, 0xff, 0xff, 0xff);
    } else {
        throw std::runtime_error("Failed to init sdlimage");
    }
}

void SDL_IO::drawComponent(const Component& c)
{
    std::cout <<
        "Drawing component: " <<
        c.X() << " " << c.Y() << " " <<
        c.Width()  << " " << c.Height() << std::endl;

    SDL_Rect dest = { c.X(), c.Y(), c.X() + c.Width(), c.Y() + c.Height() };
    SDL_BlitSurface(c.surfPointer(), nullptr, buffer.get(), &dest);
}

void SDL_IO::drawLine(int x1, int y1, int x2, int y2)
{
    //TODO: this is a hack
    lineSegments.push_back(
            std::pair<SDL_Point, SDL_Point>({x1, y1}, {x2, y2})
            );
}

std::unique_ptr<MenuComponent> SDL_IO::createMenuComponent(int x, int y, int w, int h)
{
    SurfacePointer surf(
            SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000),
            SDL_FreeSurface
            );

    return std::unique_ptr<MenuComponent>(
            new MenuComponent(x, y, w, h, std::move(surf))
            );
}

std::unique_ptr<Button> SDL_IO::createButton(int x, int y, int w, int h)
{
    SurfacePointer surf(
            SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000),
            SDL_FreeSurface
            );

    return std::unique_ptr<Button>(
            new Button(x, y, w, h, std::move(surf))
            );
}

std::unique_ptr<ModelView> SDL_IO::createModelView(int x, int y, int w, int h, const Model& m)
{
    SurfacePointer surf(
            SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000),
            SDL_FreeSurface
            );

    return std::unique_ptr<ModelView>(
            new ModelView(x, y, w, h, m, std::move(surf))
            );
}

SDL_IO::RendererPointer SDL_IO::createSoftwareRenderer(const Component& c)
{
    return RendererPointer(
            SDL_CreateSoftwareRenderer(c.surfPointer()), SDL_DestroyRenderer
            );
}

SDL_IO::RendererPointer SDL_IO::createSoftwareRenderer()
{
    auto renderer = SDL_CreateSoftwareRenderer(rootComponent->surfPointer());
    return RendererPointer(renderer, SDL_DestroyRenderer);
}

int SDL_IO::getWidth() const noexcept
{
    return screenWidth;
}

int SDL_IO::getHeight() const noexcept
{
    return screenHeight;
}

void SDL_IO::setHeight(int h) noexcept
{
    screenHeight = h;
}

void SDL_IO::setWidth(int w) noexcept
{
    screenWidth = w;
}

void SDL_IO::CycleTexture()
{
    screenTexture.reset(SDL_CreateTexture(renderer.get(),
                    SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                    screenWidth, screenHeight));
    buffer.reset(SDL_CreateRGBSurface(0, screenWidth, screenHeight, 32,
            0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000));
    SDL_FillRect(buffer.get(), nullptr, 0xffffffff);
}

void SDL_IO::loadImage(std::string imgPath, std::string imgKey)
{
    SDL_Surface *tmp = IMG_Load(imgPath.c_str());
    if (!tmp) {
        throw std::runtime_error("Failed to load image " + imgPath);
    }
    SDL_Surface *end = SDL_ConvertSurface(tmp, buffer->format, 0);
    texMap[imgKey] = end;
    SDL_FreeSurface(tmp);
}

void SDL_IO::renderImage(std::string key, int x, int y)
{
    SDL_Surface *surf = texMap[key];
    if (surf) {
        SDL_Rect destRect = {
            x, y, x + surf->w, y + surf->h
        };
        SDL_BlitSurface(surf, nullptr, buffer.get(), &destRect);
    } else {
        std::cout << "Failed to find surface for key " << key << std::endl;
    }
}

void SDL_IO::setColor(unsigned int rgba)
{
    SDL_SetRenderDrawColor(renderer.get(),
            rgba & 0x00ff0000,
            rgba & 0x0000ff00,
            rgba & 0x000000ff,
            rgba & 0xff000000);
    currentDrawColor = rgba;
}

void SDL_IO::drawRectangle(int x1, int y1, int x2, int y2)
{
    SDL_Rect destRect = { x1, y1, x2, y2 };
    SDL_FillRect(buffer.get(), &destRect, currentDrawColor);
}

void SDL_IO::drawRectangle(const SurfacePointer& s, int x1, int y1, int x2, int y2)
{
    SDL_Rect destRect = { x1, y1, x2, y2 };
    SDL_FillRect(s.get(), &destRect, currentDrawColor);
}

void SDL_IO::updateScreen()
{
    rootComponent->invalidate();
    auto r = createSoftwareRenderer();
    DrawingContext dc(*this, std::move(r));
    rootComponent->update(dc);
    SDL_UpdateTexture(screenTexture.get(), nullptr, buffer->pixels, buffer->pitch);
    SDL_RenderCopy(renderer.get(), screenTexture.get(), nullptr, nullptr);

    //TODO: this is an awful hack
    SDL_SetRenderDrawColor(renderer.get(), 0xff, 0xff, 0xff, 0xff);
    for (auto& line : lineSegments) {
        SDL_RenderDrawLine(renderer.get(), line.first.x, line.first.y, line.second.x, line.second.y);
    }
    SDL_RenderPresent(renderer.get());
    //SDL_FillRect(buffer.get(), nullptr, 0xffffffff);
}

bool SDL_IO::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            return false;
        else if (e.type == SDL_WINDOWEVENT) {
            switch(e.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                screenWidth = e.window.data1;
                screenHeight = e.window.data2;
                CycleTexture();
                break;
            }
        } else if (e.type == SDL_MOUSEBUTTONDOWN) {
            EventArgs args{ e.button.x, e.button.y, true };
            if (!rootComponent->handleEvent(args))
                std::cout << "unhandled mouse event" << std::endl;
            return true;
        } else if (e.type == SDL_MOUSEBUTTONUP) {
            EventArgs args{ e.button.x, e.button.y, false };
            if (!rootComponent->handleEvent(args))
                std::cout << "unhandled mouse event" << std::endl;
            return true;
        }
    }
    return true;
}

Uint32 SDL_IO::getTicks()
{
    return SDL_GetTicks();
}

void SDL_IO::doDelay(Uint32 ms)
{
    SDL_Delay(ms);
}

SDL_IO::~SDL_IO()
{
    std::cout << "~SDL_IO" << std::endl;
    for (auto it = texMap.begin(); it != texMap.end(); it++) {
        SDL_FreeSurface(it->second);
    }
}
