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

#ifndef __LEUCHT_SCREEN_H__
#define __LEUCHT_SCREEN_H__

#include "types.h"

#include <vector>
#include <thread>
#include <atomic>

#include <cstdint>

class Screen
{
public:
    Screen(uint32_t w, uint32_t h, uint32_t layers);
    ~Screen();

    void draw();

    /**
     * Clear scene (All pixels off in all layers)
     */
    void clear();

    /**
     * Clear layer scene.
     *
     * @param layer         layer to clear
     */
    void clear(uint32_t layer);

    /**
     * Set specific pixel color.
     * This does not test whether a_x and a_y are in the dimensions!
     *
     * @param x             x-position
     * @param y             y-position
     * @param layer         layer to paint to (0 is background, n is foreground)
     * @param colour        colour
     */
    void set(uint32_t x, uint32_t y, uint32_t layer, colour_alpha_t colour);

    /**
     * @brief Write text to screen.
     *
     * @param x             x-position
     * @param y             y-position
     * @param layer         layer to paint to (0 is background, n is foreground)
     * @param colour        colour
     * @param msg           string to write
     * @param offset        offset (use for moving text)
     */
    void write(uint32_t x, uint32_t y, uint32_t layer, colour_alpha_t colour, const std::string& msg, int32_t offset = 0);

    uint32_t width() const { return w_; }
    uint32_t height() const { return h_; }

    void fill(colour_alpha_t colour, uint32_t layer);

    std::vector<colour_t> blend() const;

protected:
    // Disable copy
    Screen(const Screen& val);
    Screen& operator=(const Screen& a_val);

private:
    uint32_t w_;
    uint32_t h_;
    uint32_t layerCount_;
    int32_t usedLayer_ = 1;
    uint32_t pixelCount_;

    typedef std::vector<colour_alpha_t> screen_alpha_t;
    std::vector<screen_alpha_t> layers_;
};

#endif  // __LEUCHT_SCREEN_H__
