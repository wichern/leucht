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

#ifndef __LEUCHT_ENGINE_RENDERER_H__
#define __LEUCHT_ENGINE_RENDERER_H__

#include "Screen.h"

#include <SDL/SDL.h>

#include <cstdint>

namespace engine {

class Renderer
{
public:
    Renderer() = default;
    ~Renderer();

    bool init(uint32_t w, uint32_t h, bool bcm2835, bool sdl, int pixelSize = 20);

    void render(const Screen& screen);

private:
    bool bcm2835_ = false;
    SDL_Surface* screen_ = nullptr;
    SDL_Surface* image_ = nullptr;
    int pixelSize_ = 1;
};

}  // namespace engine

#endif  // __LEUCHT_ENGINE_RENDERER_H__
