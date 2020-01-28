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

#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
    ::srand(::time(NULL));

    int port = 8080;
    if (argc >= 2)
        port = std::stol(argv[1]);

#ifdef SDL_RENDERING
    // Check where we want to output
    bool bcm2835 = false;
    bool sdl = false;
    if (argc >= 3) {
        bcm2835 = 0 == strcmp(argv[2], "bcm2835");
        sdl = 0 == strcmp(argv[2], "sdl");
        if (argc >= 4) {
            bcm2835 &= 0 == strcmp(argv[3], "bcm2835");
            sdl &= 0 == strcmp(argv[3], "sdl");
        }
    }

    // default to SDL
    if (!bcm2835)
        sdl = true;
#else
    bool bcm2835 = true;
    bool sdl = false;
#endif

    engine::Game game(21, 12);
    if (!game.init(port, bcm2835, sdl))
        return EXIT_FAILURE;

    game.run();

    return EXIT_SUCCESS;
}
