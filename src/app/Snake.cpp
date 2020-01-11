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

#include "app/Snake.h"
#include "Screen.h"

#include <algorithm>
#include <cstdlib>

namespace app {

void Snake::init(Screen& screen)
{
    screen.clear();

    initSnake(screen.width(), screen.height());
}

void Snake::update(Screen& screen)
{
    screen.clear();

    switch (state_) {
    case StateWaiting:
    {
        screen.write(5, 3, 1, colour_alpha_t(0, 0, 127), std::to_string(gameSpeed_).c_str());
        drawSnake(screen);
        drawFruit(screen);
    } break;
    case StateRunning:
    {
        if (0 == waiter_) {
            waiter_ = gameSpeed_;
            updateSnake();
        } else {
            waiter_--;
        }

        drawSnake(screen);
        drawFruit(screen);
    } break;
    case StateLostAnimation:
    {
        if (0 == lostCountdown_) {
            // Decrease game speed.
            gameSpeed_ += 1;
            initSnake(w_, h_); // restart
        } else {
            lostCountdown_--;

            screen.fill(colour_alpha_t(127, 0, 0), 1);
            drawSnake(screen);
            drawFruit(screen);
            screen.write(3, 3, 0, colour_alpha_t(255, 0, 0), "LOST");
        }
    } break;
    case StateWon:
    {
        if (0 == wonCountdown_) {
            // Increase game speed.
            if (gameSpeed_ > 1) {
                gameSpeed_ -= 2;
            }
            initSnake(w_, h_); // restart
        } else {
            wonCountdown_--;

            screen.fill(colour_alpha_t(0, 127, 0), 1);
            drawSnake(screen);
            drawFruit(screen);
            screen.write(3, 3, 0, colour_alpha_t(0, 255, 0), "WON");
        }
    } break;
    }
}

void Snake::close()
{

}

void Snake::keyPressed(Key key)
{
    if (state_ == StateWaiting)
        state_ = StateRunning;

    // do not allow opposite directions
    if (!tail_.empty()) {
        switch (direction_) {
        case 0: // Up
        {
            if (key == Key_Down)
                return;
        } break;
        case 1: // Left
        {
            if (key == Key_Right)
                return;
        } break;
        case 2: // Right
        {
            if (key == Key_Left)
                return;
        } break;
        case 3: // Down
        {
            if (key == Key_Down)
                return;
        } break;
        }
    }
    direction_ = key;
}

void Snake::initSnake(uint32_t w, uint32_t h)
{
    state_ = StateWaiting;
    waiter_ = 0;

    w_ = w;
    h_ = h;

    direction_ = 0;

    // Start at center:
    head_ = { w_ / 2, h_ / 2 };
    tail_.clear();

    placeFruit();
}

void Snake::drawSnake(Screen& screen)
{
    screen.set(head_.first, head_.second, 0, colour_alpha_t(255, 255, 255, 127));
    for (const auto& t : tail_)
        screen.set(t.first, t.second, 0, colour_alpha_t(255, 255, 255, 127));
}

void Snake::drawFruit(Screen& screen)
{
    screen.set(fruit_.first, fruit_.second, 0, colour_alpha_t(0, 255, 0, 127));
}

void Snake::placeFruit()
{
    uint32_t freeFields = (w_ * h_) - 1 - tail_.size();
    int rnd = ::rand() % freeFields;

    for (uint32_t y = 0; y < h_; ++y) {
        for (uint32_t x = 0; x < w_; ++x) {
            std::pair<uint32_t, uint32_t> p(x, y);
            if (p != head_ && std::find(tail_.begin(), tail_.end(), p) == tail_.end()) {
                if (0 == rnd) {
                    fruit_ = p;
                    return;
                } else {
                    rnd--;
                }
            }
        }
    }

    int impossible = 0;
    (void)impossible;
}

void Snake::updateSnake()
{
    // Remove last tail position.
    std::pair<uint32_t, uint32_t> tailEnd;
    if (tail_.empty()) {
        tailEnd = head_;
    } else {
        tailEnd = tail_.back();
        tail_.pop_back();

        // Add head to tail.
        tail_.push_front(head_);
    }

    // Move head to next position.
    switch (direction_) {
    case 0:  // UP
    {
        if (0 == head_.second)
            head_.second = h_;
        head_.second--;
    } break;
    case 1:  // Left
    {
        if (0 == head_.first)
            head_.first = w_;
        head_.first--;
    } break;
    case 2:  // Right
    {
        head_.first++;
        if (w_ == head_.first)
            head_.first = 0;
    } break;
    case 3:  // Down
    {
        head_.second++;
        if (h_ == head_.second)
            head_.second = 0;
    } break;
    }

    // Check whether the head touches its tail:
    if (std::find(tail_.begin(), tail_.end(), head_) != tail_.end()) {
        state_ = StateLostAnimation;
        lostCountdown_ = 5*30; // 5 seconds
    } else {
        // Check whether the head touches the fruit.
        if (head_ == fruit_) {
            // Re-add tail end.
            tail_.push_back(tailEnd);
            placeFruit();
        }
    }

    if ((tail_.size() + 1) == (w_ * h_)) {
        state_ = StateWon;
        wonCountdown_ = 5*30; // 5 seconds
    }
}

}  // namespace app
