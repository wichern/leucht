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

#include "app/Colour.h"
#include "Screen.h"

namespace app {

static colour_alpha_t S_colours[] {
    colour_alpha_t(255, 0, 0),
    colour_alpha_t(0, 255, 0),
    colour_alpha_t(0, 0, 255)
};

static int S_colourCount = sizeof(S_colours) / sizeof(S_colours[0]);

void Colour::init(Screen& screen)
{
    screen.clear();
}

void Colour::update(Screen& screen)
{
    screen.fill(S_colours[current_], 0);
}

void Colour::close()
{

}

void Colour::keyPressed(Key key)
{
    switch (key) {
    case Key_Up:
    case Key_Right:
    {
        current_--;
    } break;
    case Key_Down:
    case Key_Left:
    {
        current_++;
    } break;
    }

    if (current_ < 0) {
        current_ = S_colourCount - 1;
    } else if (current_ >= S_colourCount) {
        current_ = 0;
    }
}

}  // namespace app
