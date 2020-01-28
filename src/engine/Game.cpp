/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Paul Wichern
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "engine/Game.h"

#include "app/Welcome.h"
#include "app/Colour.h"
#include "app/Clock.h"
#include "app/Radio.h"
#include "app/Snake.h"

#ifdef SDL_RENDERING
#include <SDL/SDL.h>
#endif

namespace engine {

Game::Game(uint32_t w, uint32_t h)
    : screen_(w, h, 8), appSwitchSignal_(-1), keyPressedEvent_(-1)
{

}

Game::~Game()
{
    for (app::IApp* app : apps_) {
        delete app;
    }

    if (webApi_) {
        delete webApi_;
    }

    delete renderer_;

#ifdef SDL_RENDERING
    SDL_Quit();
#endif
}

bool Game::init(int port, bool bcm2835, bool sdl)
{
    assert(apps_.empty());

    apps_.push_back(new app::Welcome);
    apps_.push_back(new app::Colour);
    apps_.push_back(new app::Clock);
    apps_.push_back(new app::Radio);
    apps_.push_back(new app::Snake);

    apps_[activeApp_]->init(screen_);

    webApi_ = new LeuchtAPI(port, apps_, appSwitchSignal_, keyPressedEvent_);
    webApi_->init(activeApp_);

#ifdef SDL_RENDERING
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }
#endif

    renderer_ = new Renderer();
    return renderer_->init(screen_.width(), screen_.height(), bcm2835, sdl);
}

void Game::run()
{
    bool running = true;

    auto currentTime = std::chrono::high_resolution_clock::now();
    const auto deltaUpdateTime = std::chrono::nanoseconds(1000000000/24);  // 24fps
    const auto deltaRenderTime = std::chrono::nanoseconds(1000000000/60);  // 60fps
    auto nextUpdate = currentTime;
    auto nextRender = currentTime;

    while (running) {
#ifdef SDL_RENDERING
        SDL_Event event;
        SDL_PollEvent(&event);

        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        }
#endif

        int switchApp = appSwitchSignal_;
        if (switchApp != -1) {
            appSwitchSignal_ = -1;
            if (activeApp_ != switchApp) {
                apps_[activeApp_]->close();
                activeApp_ = switchApp;
                apps_[activeApp_]->init(screen_);
            }
        }

        int key = keyPressedEvent_;
        if (-1 != key) {
            apps_[activeApp_]->keyPressed(static_cast<Key>(key));
            keyPressedEvent_ = -1;
        }

        auto now = std::chrono::high_resolution_clock::now();

        while (nextUpdate < now) {
            apps_[activeApp_]->update(screen_);
            nextUpdate += deltaUpdateTime;
        }

        if (nextRender < now) {
            renderer_->render(screen_);
            while (nextRender < now)
                nextRender += deltaRenderTime;
        }

        std::this_thread::sleep_until(std::min(nextUpdate, nextRender));
    }
}

}  // namespace engine
