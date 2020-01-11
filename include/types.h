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

#ifndef __LEUCHT_TYPES_H__
#define __LEUCHT_TYPES_H__

#include <cstdint>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} colour_t;

typedef union colour_alpha_t {
    colour_alpha_t() : val(0) {}
    explicit colour_alpha_t(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}
    explicit colour_alpha_t(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
    explicit colour_alpha_t(colour_t c) : r(c.r), g(c.g), b(c.b), a(255) {}

    operator colour_t() const { return { r, g, b }; }

    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    uint32_t val;
} colour_alpha_t;

/**
 * Integer alpha blending.
 *
 * @param fg          foreground colour
 * @param bg          background colour
 * @return            blended colour
 */
inline colour_t blend(colour_alpha_t fg, colour_t bg)
{
    uint32_t alpha = fg.a + 1;
    uint32_t inv_alpha = 256 - fg.a;

    colour_t ret;
    ret.r = (uint8_t) ((alpha * fg.r + inv_alpha * bg.r) >> 8);
    ret.g = (uint8_t) ((alpha * fg.g + inv_alpha * bg.g) >> 8);
    ret.b = (uint8_t) ((alpha * fg.b + inv_alpha * bg.b) >> 8);

    return ret;
}

enum Key {
    Key_Up = 0,
    Key_Left,
    Key_Right,
    Key_Down
};

#endif  // __LEUCHT_TYPES_H__
