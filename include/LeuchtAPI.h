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

#ifndef __LEUCHT_LEUCHTAPI_H__
#define __LEUCHT_LEUCHTAPI_H__

#include <pistache/endpoint.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include "app/IApp.h"

#include <atomic>
#include <vector>
#include <map>

/**
 * @brief The LeuchtAPI class provides a RESTful api for interaction via browser.
 */
class LeuchtAPI
{
public:
    LeuchtAPI(
            int port,
            const std::vector<app::IApp*>& apps,
            std::atomic<int>& appSwitcher,
            std::atomic<int>& keyPressed);

    void init(size_t activeApp);

private:
    void doSetActiveApp(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void doGetActiveApp(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void doGetApps(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void doKeyPressed(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void doGetIndexHTML(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);
    void doGetScript(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint_;
    Pistache::Rest::Router router_;

    size_t activeApp_;
    const std::vector<app::IApp*>& apps_;
    std::atomic<int>& appSwitcher_;
    std::atomic<int>& keyPressed_;
};

#endif  // __LEUCHT_LEUCHTAPI_H__
