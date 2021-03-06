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

#include "engine/Renderer.h"

#ifdef SDL_RENDERING
#include <SDL/SDL.h>
#endif

#include "bcm2835.h"

#include <iostream>

namespace engine {

Renderer::~Renderer()
{
#ifdef SDL_RENDERING
    if (bcm2835_) {
        bcm2835_spi_end();
    }

    if (image_) {
        SDL_FreeSurface(image_);
    }

    if (screen_) {
        SDL_FreeSurface(screen_);
    }

//    if (surface_) {
//        SDL_FreeSurface(surface_);
//    }

//    if (window_) {
//        SDL_DestroyWindow(window_);
//    }
#endif
}

bool Renderer::init(uint32_t w, uint32_t h, bool bcm2835, bool sdl, int pixelSize)
{
    if (bcm2835) {
        if (1 != bcm2835_init()) {
            return false;
        }
        if (1 != bcm2835_spi_begin()) {
            std::cerr << "BCM2835 does not support running in group 'gpio'. Please start as root." << std::endl;
            return false;
        }

        bcm2835_ = true;

        bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
        bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);

        // a value of 256 lead to flickering, whereas 128 lead to some leds not
        // updating at all.
        // The lower the given value, the faster the leds can be updated:
        //
        // 256 ... 976.5625kHz
        // 128 ... 1.953125MHz
        //
        // in order to get 30 fps at 252 with each 24 bit color data we would
        // need a clock speed of 30*252*24 = 181.440kHz (at least!)
        bcm2835_spi_setClockDivider(128 + 32);
    }

    if (sdl) {
#ifdef SDL_RENDERING
        pixelSize_ = pixelSize;

        screen_ = SDL_SetVideoMode(w * pixelSize, h * pixelSize, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);
        if (!screen_) {
            std::cerr << "SDL_SetVideoMode: " << SDL_GetError() << std::endl;
            return false;
        }

        image_ = SDL_CreateRGBSurface(
                    0,
                    static_cast<int>(w) * pixelSize,
                    static_cast<int>(h) * pixelSize,
                    32,
                    0,
                    0,
                    0,
                    0);

        if (!image_) {
            std::cerr << "SDL_CreateRGBSurface: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(screen_);
            screen_ = nullptr;
            return false;
        }
#else
        (void)w;
        (void)h;
        (void)pixelSize;
        std::cerr << "SDL not supported!" << std::endl;
#endif
    }

    return true;
}

void Renderer::render(const Screen& screen)
{
    std::vector<colour_t> merged = screen.blend();

    if (bcm2835_) {
        // The Pixels are arranged like this on the wall:
        //
        // 16 -- 17 -- 18 -- 19 -- 20 -- 21 -- 22 -- 23
        //  |
        // 15 -- 14 -- 13 -- 12 -- 11 -- 10 -- 09 -- 08
        //                                           |
        // 00 -- 01 -- 02 -- 03 -- 04 -- 05 -- 06 -- 07
        //
        // The colour vector is arranged like this:
        //
        // 00 -- 01 -- 02 -- 03 -- 04 -- 05 -- 06 -- 07
        //
        // 08 -- 09 -- 10 -- 11 -- 12 -- 13 -- 14 -- 15
        //
        // Therfore this array has to be converted:
        std::vector<colour_t> rearranged;
        rearranged.resize(merged.size());

        uint32_t idx = 0;
        for (uint32_t y = 0; y < screen.height(); ++y) {
            for (uint32_t x = 0; x < screen.width(); ++x) {
                if (y & 1) {  // Odd row
                    rearranged[(1 + y) * screen.width() - x] = merged[idx];
                } else {  // Even row
                    rearranged[x + (y * screen.width())] = merged[idx];
                }
                ++idx;
            }
        }

        bcm2835_spi_writenb(reinterpret_cast<char*>(rearranged.data()), rearranged.size() * 3);
        //bcm2835_spi_transfern(reinterpret_cast<char*>(rearranged.data()), rearranged.size() * 3);

        // Data is latched by holding clock pin low for 1 millisecond
        // @todo: really neccessary?
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

#ifdef SDL_RENDERING
    if (screen_) {
        Uint32* pixels = (Uint32 *)image_->pixels;

        for (int y = 0; y < image_->h / pixelSize_; ++y) {
            for (int x = 0; x < image_->w / pixelSize_; ++x) {
                const colour_t& pixel = merged[(y * (image_->w / pixelSize_)) + x];
                Uint32 sdlPixel = SDL_MapRGB(image_->format, pixel.r, pixel.g, pixel.b);
                for (int py = y * pixelSize_; py < y * pixelSize_ + pixelSize_; ++py) {
                    for (int px = x * pixelSize_; px < x * pixelSize_ + pixelSize_; ++px) {
                        pixels[(py * (image_->w)) + px] = sdlPixel;
                    }
                }
            }
        }

        if (0 != SDL_BlitSurface(image_, nullptr, screen_, nullptr)) {
            std::cerr << "SDL_BlitSurface: " << SDL_GetError() << std::endl;
        } else {
            if (0 != SDL_Flip(screen_)) {
                std::cerr << "SDL_Flip: " << SDL_GetError() << std::endl;
            }
//            if (0 != SDL_UpdateWindowSurface(screen_)) {
//                std::cerr << "SDL_UpdateWindowSurface: " << SDL_GetError() << std::endl;
//            }
        }
    }
#endif
}

}  // namespace engine
