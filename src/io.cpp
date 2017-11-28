#include "io.h"
#include "component.h"
#include "appcomponent.h"
#include "modelview.h"

#include <utility>
#include <iostream>
#include <map>

SDL_IO::SDL_IO(int width, int height)
    : SDLBaseIO(),
      window(nullptr, SDL_DestroyWindow),
      renderer(nullptr, SDL_DestroyRenderer),
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
        SDL_SetRenderDrawColor(renderer.get(), 0xff, 0xff, 0xff, 0xff);
    } else {
        throw std::runtime_error("Failed to init sdlimage");
    }
}

void SDL_IO::drawComponent(const Component& c)
{
    SDL_SetRenderTarget(renderer.get(), nullptr);
    SDL_Rect dest = {
        c.X(), c.Y(), c.Width(), c.Height()
    };
    SDL_RenderCopy(renderer.get(), c.texturePointer(), nullptr, &dest);
}

void SDL_IO::drawLine(int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer.get(), x1, y1, x2, y2);
}

std::unique_ptr<MenuComponent> SDL_IO::createMenuComponent(int x, int y, int w, int h)
{
    TexturePointer tex(
            SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_ARGB8888, 
                SDL_TEXTUREACCESS_TARGET, w, h),
            SDL_DestroyTexture
            );

    return std::unique_ptr<MenuComponent>(
            new MenuComponent(x, y, w, h, std::move(tex))
            );
}

std::unique_ptr<Button> SDL_IO::createButton(int x, int y, int w, int h)
{
    TexturePointer tex(
            SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_ARGB8888, 
                SDL_TEXTUREACCESS_TARGET, w, h),
            SDL_DestroyTexture
            );

    return std::unique_ptr<Button>(
            new Button(x, y, w, h, std::move(tex))
            );
}

std::unique_ptr<ModelView> SDL_IO::createModelView(int x, int y, int w, int h, Model& m)
{
    TexturePointer tex(
            SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_ARGB8888, 
                SDL_TEXTUREACCESS_TARGET, w, h),
            SDL_DestroyTexture
            );

    return std::unique_ptr<ModelView>(
            new ModelView(x, y, w, h, m, std::move(tex))
            );
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

void SDL_IO::loadImage(std::string imgPath, std::string imgKey)
{
    SDL_Surface *tmp = IMG_Load(imgPath.c_str());
    if (!tmp) {
        throw std::runtime_error("Failed to load image " + imgPath);
    }
    TexturePointer tex(SDL_CreateTextureFromSurface(renderer.get(), tmp), SDL_DestroyTexture);

    texMap.insert(std::make_pair(imgKey, std::move(tex)));

    SDL_FreeSurface(tmp);
}

void SDL_IO::renderImage(std::string key, int x, int y)
{
    const auto& tex = texMap[key];
    if (tex) {
        int w, h;
        SDL_QueryTexture(tex.get(), nullptr, nullptr, &w, &h);
        SDL_Rect destRect = {
            x, y, x + w, y + h
        };
        SDL_RenderCopy(renderer.get(), tex.get(), nullptr, &destRect);
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

void SDL_IO::setColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
}

void SDL_IO::drawRectangle(int x1, int y1, int x2, int y2)
{
    SDL_Rect destRect = { x1, y1, x2, y2 };
    SDL_RenderFillRect(renderer.get(), &destRect);
}

void SDL_IO::setRenderTarget(const std::unique_ptr<Component>& c)
{
    if (c != nullptr)
        SDL_SetRenderTarget(renderer.get(), c->texturePointer());
    else
        SDL_SetRenderTarget(renderer.get(), nullptr);
}

void SDL_IO::setRenderTarget(const Component& c)
{
    SDL_SetRenderTarget(renderer.get(), c.texturePointer());
}

void SDL_IO::updateScreen()
{
    rootComponent->invalidate();

    DrawingContext dc(*this, renderer);
    rootComponent->update(dc);

    SDL_RenderPresent(renderer.get());
}

bool SDL_IO::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            return false;
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
}
