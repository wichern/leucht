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

#include "LeuchtAPI.h"

#include "resources/IndexHtml.h"
#include "resources/LeuchtScript.h"

#include <pistache/http_header.h>
#include <pistache/mime.h>

using namespace Pistache;

LeuchtAPI::LeuchtAPI(
        int port,
        const std::vector<app::IApp*>& apps,
        std::atomic<int>& appSwitcher,
        std::atomic<int>& keyPressed)
    : httpEndpoint_(std::make_shared<Http::Endpoint>(Address{Ipv4::any(), Port(port)})),
      apps_(apps),
      appSwitcher_(appSwitcher),
      keyPressed_(keyPressed)
{

}

void LeuchtAPI::init(size_t activeApp)
{
    assert(activeApp >= 0 && activeApp < apps_.size());

    activeApp_ = activeApp;

    auto opts = Http::Endpoint::options()
            .flags(Tcp::Options::ReuseAddr);
    httpEndpoint_->init(opts);

    using namespace Rest;
    Routes::Post(router_, "/api/app/activate/:app?", Routes::bind(&LeuchtAPI::doSetActiveApp, this));
    Routes::Get(router_, "/api/app/list", Routes::bind(&LeuchtAPI::doGetApps, this));
    Routes::Get(router_, "/api/app/active", Routes::bind(&LeuchtAPI::doGetActiveApp, this));
    Routes::Post(router_, "/api/app/key/:key?", Routes::bind(&LeuchtAPI::doKeyPressed, this));
    Routes::Get(router_, "/", Routes::bind(&LeuchtAPI::doGetIndexHTML, this));
    Routes::Get(router_, "/leucht.js", Routes::bind(&LeuchtAPI::doGetScript, this));

    httpEndpoint_->setHandler(router_.handler());
    httpEndpoint_->serveThreaded();
}

void LeuchtAPI::doSetActiveApp(const Rest::Request& request, Http::ResponseWriter response)
{
    int active = request.param(":app").as<int>();

    if (active < 0 || active >= apps_.size()) {
        response.send(Http::Code::Not_Found, "App \"" + std::to_string(active) + "\" does not exist");
    } else {
        activeApp_ = active;
        appSwitcher_ = activeApp_;
        response.headers().add<Http::Header::ContentType>(MIME(Text, Plain));
        response.send(Http::Code::Ok, std::to_string(activeApp_).c_str());
    }
}

void LeuchtAPI::doGetActiveApp(const Rest::Request&, Http::ResponseWriter response)
{
    response.headers().add<Http::Header::ContentType>(MIME(Text, Plain));
    response.send(Http::Code::Ok, std::to_string(activeApp_).c_str());
}

void LeuchtAPI::doGetApps(const Rest::Request&, Http::ResponseWriter response)
{
    std::string ret("[");
    for (size_t i = 0; i < apps_.size(); ++i) {
        ret += '"';
        ret += apps_[i]->name();
        ret += '"';
        if (i + 1 < apps_.size())
            ret += ',';
    }
    ret += ']';

    response.headers().add<Http::Header::ContentType>(MIME(Text, Json));
    response.send(Http::Code::Ok, ret);
}

void LeuchtAPI::doKeyPressed(const Rest::Request& request, Http::ResponseWriter response)
{
    keyPressed_ = request.param(":key").as<int>();
    response.send(Http::Code::Ok);
}

void LeuchtAPI::doGetIndexHTML(const Rest::Request&, Http::ResponseWriter response)
{
    response.send(Http::Code::Ok, resource::IndexHTML, MIME(Text, Html));
}

void LeuchtAPI::doGetScript(const Rest::Request&, Http::ResponseWriter response)
{
    response.send(Http::Code::Ok, resource::LeuchtScript, MIME(Text, Javascript));
}
