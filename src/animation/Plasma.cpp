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

#include "animation/Plasma.h"

#include "Screen.h"

#include <mutex>
#include <cmath>

namespace animation {

static float S_sintable[2880];  // Precalculated sin table
static float S_costable[2880];  // Precalculated cos table
static std::once_flag S_tablesFlag;

Plasma::Plasma(Screen& screen)
    : AnimationBase(screen)
{
    // pre-calculate sin/cos tables
    std::call_once(S_tablesFlag, []
    {
        const float c_deg = 0.017453292519943296f;
        for (int a = 0; a < 2880; a++) {
            S_sintable[a] = ::sin(a * c_deg);
            S_costable[a] = ::cos(a * c_deg);
        }
    });
}

void Plasma::init(colour_alpha_t start, colour_alpha_t end)
{
    generate(start, end);
    update();
}

void Plasma::update()
{
    ++cos_counter_;  // Change these additions
    ++sin_counter_;  // for different speed X+Y.

    if (cos_counter_ > 2880)
      cos_counter_ -= 2880;
    if (sin_counter_ > 2880)
      sin_counter_ -= 2880;

    ca1_ = 20.0f + 39.0f * S_costable[cos_counter_]; // You can play with these vars.
    ca2_ = 10.0f + 39.0f * S_sintable[sin_counter_]; // Strange things may happen though.
}

void Plasma::draw(uint32_t layer)
{
    for (uint32_t y = 0; y < screen_.height(); ++y) {
        float cv1 = abs(2.0f + (ca1_ * S_sintable[sin_counter_ + y]));
        for (uint32_t x = 0; x < screen_.width(); ++x) {
            float cv2 = abs(3.0f + (ca2_ * S_costable[cos_counter_ + x]));

            colour_alpha_t colour = colourtable_[((int) (cv1 * cv2)) % ColourCount];

            screen_.set(x, y, layer, colour);
        }
    }
}

void Plasma::generate(colour_alpha_t start, colour_alpha_t end)
{
    int l_diff_r = static_cast<int>(end.r) - static_cast<int>(start.r);
    int l_diff_g = static_cast<int>(end.g) - static_cast<int>(start.g);
    int l_diff_b = static_cast<int>(end.b) - static_cast<int>(start.b);

    float l_increment_r = static_cast<float>(l_diff_r)
    / (((float) ColourCount) / 2.0f);
    float l_increment_g = static_cast<float>(l_diff_g)
    / (((float) ColourCount) / 2.0f);
    float l_increment_b = static_cast<float>(l_diff_b)
    / (((float) ColourCount) / 2.0f);

    float l_r = static_cast<float>(start.r);
    float l_g = static_cast<float>(start.g);
    float l_b = static_cast<float>(start.b);

    for (int i = 0; i < ColourCount; ++i) {
        if (i < (ColourCount >> 1)) {
            l_r += l_increment_r;
            l_g += l_increment_g;
            l_b += l_increment_b;
        } else {
            l_r -= l_increment_r;
            l_g -= l_increment_g;
            l_b -= l_increment_b;
        }

        colourtable_[i] = colour_alpha_t(
                    static_cast<uint8_t>(l_r),
                    static_cast<uint8_t>(l_g),
                    static_cast<uint8_t>(l_b));
    }
}

}  // namespace animation
