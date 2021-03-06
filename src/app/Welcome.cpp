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

#include "app/Welcome.h"
#include "Screen.h"

#include <iostream>

namespace app {

void Welcome::init(Screen& screen)
{
    screen.clear();
    screen.write(1 + 0, 3, 0, colour_alpha_t(255, 0, 0), "L");
    screen.write(1 + 3, 3, 0, colour_alpha_t(0, 255, 0), "E");
    screen.write(1 + 6, 3, 0, colour_alpha_t(0, 0, 255), "U");
    screen.write(1 + 9, 3, 0, colour_alpha_t(255, 0, 255), "C");
    screen.write(1 + 12, 3, 0, colour_alpha_t(255, 255, 0), "H");
    screen.write(1 + 15, 3, 0, colour_alpha_t(0, 255, 255), "T");
}

void Welcome::update(Screen& screen)
{
    (void)screen;
}

void Welcome::close()
{

}

void Welcome::keyPressed(Key key)
{
    std::cout << "Key: " << key << std::endl;
}

}  // namespace app
