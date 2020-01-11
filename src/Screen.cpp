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

#include "Screen.h"
#include "font.h"

#include <SDL/SDL.h>

#include <algorithm>
#include <chrono>
#include <iostream>

Screen::Screen(uint32_t w, uint32_t h, uint32_t layers)
    : w_(w),
      h_(h),
      layerCount_(layers),
      pixelCount_(w * h)
{
    static const colour_alpha_t canull;
    layers_.resize(layerCount_);
    for (uint32_t i = 0; i < layerCount_; ++i) {
        layers_[i].resize(pixelCount_);
        std::fill(layers_[i].begin(), layers_[i].end(), canull);
    }
}

Screen::~Screen()
{

}

void Screen::clear()
{
    static const colour_alpha_t canull;
    for (uint32_t l = 0; l < layerCount_; ++l) {
        std::fill(layers_[l].begin(), layers_[l].end(), canull);
    }
    usedLayer_ = 1;
}

void Screen::clear(uint32_t layer)
{
    static const colour_alpha_t canull;
    std::fill(layers_[layer].begin(), layers_[layer].end(), canull);
}

void Screen::set(uint32_t x, uint32_t y, uint32_t layer, colour_alpha_t colour)
{
    if (x >= w_ || y >= h_)
        return;

    layers_[layer][y * w_ + x] = colour;
    usedLayer_ = std::max(usedLayer_, static_cast<int32_t>(layer + 1));
}

void Screen::write(
        uint32_t x,
        uint32_t y,
        uint32_t layer,
        colour_alpha_t colour,
        const std::string& msg)
{
    for (char c : msg) {
        // make short space character
        if (c == 0x20) {
            x += 2;
            continue;
        }

        // is this character in our character table?
        if (c < 0x21 || c > 0x7D) {
            continue;
        }

        int idx = static_cast<int>(c) - 0x21;

        // Set all pixels of this character.
        for (uint32_t cx = 0; cx < font::simple::S_ascii_table[idx].width; ++cx) {
            for (uint32_t cy = 0; cy < 5; ++cy) {
                if (font::simple::S_ascii_table[idx].bitmask[cy][cx]) {
                    set(cx + x, cy + y, layer, colour);
                }
            }
        }

        x += font::simple::S_ascii_table[idx].width + 1;
    }
}

void Screen::fill(colour_alpha_t colour, uint32_t layer)
{
    for (uint32_t p = 0; p < pixelCount_; ++p)
        layers_[layer][p] = colour;
    usedLayer_ = std::max(usedLayer_, static_cast<int32_t>(layer + 1));
}

std::vector<colour_t> Screen::blend() const
{
    std::vector<colour_t> ret;
    ret.resize(pixelCount_);

    // start with bottom most layer
    for (uint32_t p = 0; p < pixelCount_; ++p) {
        ret[p] = layers_[usedLayer_ - 1][p];
    }

    for (int32_t l = usedLayer_ - 2; l >= 0; --l) {
        for (uint32_t p = 0; p < pixelCount_; ++p) {
            ret[p] = ::blend(layers_[l][p], ret[p]);
        }
    }

//    for (uint32_t p = 0; p < pixelCount_; ++p) {
//        ret[p] = layers_[0][p];
//    }

//    for (uint32_t l = 1; l < usedLayer_; ++l) {
//        for (uint32_t p = 0; p < pixelCount_; ++p) {
//            ret[p] = ::blend(layers_[l][p], ret[p]);
//        }
//    }

    return ret;
}
