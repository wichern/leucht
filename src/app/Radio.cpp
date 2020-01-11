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

#include "app/Radio.h"
#include "Screen.h"

#include <iostream>

#include <csignal>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

namespace app {

struct RadioStation {
    std::string name;
    std::string url;
    colour_alpha_t plasma_start;
    colour_alpha_t plasma_end;
};

static RadioStation S_stations[] = {
    { "NDR2", "http://www.ndr.de/resources/metadaten/audio/m3u/ndr2.m3u", colour_alpha_t(0, 125, 0), colour_alpha_t(15, 200, 80) },
    { "Bremen2", "http://dl-ondemand.radiobremen.de/bremenzwei.m3u", colour_alpha_t(125, 0, 0), colour_alpha_t(200, 25, 25) },
    { "Info", "http://www.ndr.de/resources/metadaten/audio/m3u/ndrinfo.m3u", colour_alpha_t(0, 0, 125), colour_alpha_t(25, 25, 200) },
    { "N-JOY", "http://www.ndr.de/resources/metadaten/audio/m3u/n-joy.m3u", colour_alpha_t(83, 172, 83), colour_alpha_t(25, 25, 200) }
};

static int S_stationCount = sizeof(S_stations) / sizeof(S_stations[0]);

Radio::~Radio()
{
    if (plasma_)
        delete plasma_;

    if (-1 != processId_)
        ::kill(processId_, SIGKILL);

    if (errThread_.joinable())
        errThread_.join();
}

void Radio::init(Screen& screen)
{
    screen.clear();
    if (!plasma_) {
        plasma_ = new animation::Plasma(screen);
    }

    startPlayer(currentStation_);
}

void Radio::update(Screen& screen)
{
    if (stationChanged_) {
        screen.clear();
        stationChanged_ = false;
    }

    // animation
    plasma_->update();
    plasma_->draw(1);
    screen.write(1, 3, 0, colour_alpha_t(255, 255, 255, 128), S_stations[currentStation_].name);
}

void Radio::close()
{
    if (-1 != processId_)
        ::kill(processId_, SIGKILL);
}

void Radio::keyPressed(Key key)
{
    switch (key) {
    case Key_Up: {
        currentStation_--;
    } break;
    case Key_Down: {
        currentStation_++;
    } break;
    default:
        return;
    }

    if (currentStation_ < 0) {
        currentStation_ = S_stationCount - 1;
    } else if (currentStation_ >= S_stationCount) {
        currentStation_ = 0;
    }

    stationChanged_ = true;
    startPlayer(currentStation_);
}

void Radio::startPlayer(int station)
{
    if (-1 != processId_)
        ::kill(processId_, SIGKILL);

    plasma_->init(
                S_stations[station].plasma_start,
                S_stations[station].plasma_end);

    if (-1 == ::pipe(pipefd_))
        ::perror("pipe");

    processId_ = ::fork();
    if (-1 == processId_) {
        perror("fork");
    } else {
        if (0 == processId_) {  // child process
            ::close(pipefd_[0]);
            //if (-1 == ::execl("/usr/bin/mplayer", "mplayer", S_stations[station].url.c_str(), NULL)) {
            if (-1 == ::execl("/usr/bin/cvlc", "cvlc", S_stations[station].url.c_str(), NULL)) {
                std::string err = "Starting player failed: ";
                err += strerror(errno);
                ::write(pipefd_[1], err.c_str(), err.length());
            }
            ::close(pipefd_[1]);
            ::exit(EXIT_FAILURE);
        }
    }

    // Spawn thread that waits for incoming error messages.
    if (errThread_.joinable())
        errThread_.join();
    errThread_ = std::thread(&Radio::errorMessageReaderThread, this);
}

void Radio::errorMessageReaderThread()
{
    ::close(pipefd_[1]);
    char buf[65];
    while (true) {
        ssize_t bytes = ::read(pipefd_[0], &buf, 64);
        if (bytes <= 0)
            break;
        buf[bytes] = 0;
        fputs(buf, stderr);
    }
    //::waitpid(processId_, NULL, 0);
    ::close(pipefd_[0]);
}

}  // namespace app
