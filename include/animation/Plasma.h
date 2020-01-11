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

#ifndef __LEUCHT_ANIMATION_PLASMA_H__
#define __LEUCHT_ANIMATION_PLASMA_H__

#include "animation/AnimationBase.h"

#include "types.h"

namespace animation {

class Plasma : public AnimationBase
{
public:
    Plasma(Screen& screen);
    ~Plasma() = default;

    void init(colour_alpha_t start, colour_alpha_t end);
    void update();
    void draw(uint32_t layer) override;

private:
    static const int ColourCount = 512;

    // Generate colour table.
    void generate(colour_alpha_t start, colour_alpha_t end);

    // Colour table
    colour_alpha_t colourtable_[ColourCount];

    uint32_t cos_counter_ = 0;
    uint32_t sin_counter_ = 0;

    float ca1_ = 0.0f;
    float ca2_ = 0.0f;
};

}  // namespace animation

#endif  // __LEUCHT_ANIMATION_PLASMA_H__
