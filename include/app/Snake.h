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

#ifndef __LEUCHT_APP_SNAKE_H__
#define __LEUCHT_APP_SNAKE_H__

#include "app/IApp.h"

#include <list>

namespace app {

class Snake : public IApp
{
public:
    ~Snake() {}

    const char* name() override { return "Snake"; }

    void init(Screen& screen) override;
    void update(Screen& screen) override;
    void close() override;
    void keyPressed(Key key) override;

private:
    void initSnake(uint32_t w, uint32_t h);
    void drawSnake(Screen& screen);
    void drawFruit(Screen& screen);
    void placeFruit();
    void updateSnake();

    enum GameState {
        StateWaiting = 0,
        StateRunning,
        StateLostAnimation,
        StateWon
    };

    GameState state_;
    int waiter_;
    int gameSpeed_ = 10;
    int lostCountdown_;
    int wonCountdown_;

    char direction_;
    uint32_t w_;
    uint32_t h_;
    std::list<std::pair<uint32_t, uint32_t>> tail_;
    std::pair<uint32_t, uint32_t> head_;
    std::pair<uint32_t, uint32_t> fruit_;
};

}  // namespace app

#endif  // __LEUCHT_APP_SNAKE_H__
