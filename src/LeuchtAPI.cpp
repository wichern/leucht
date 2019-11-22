#include "LeuchtAPI.h"

#include <pistache/http_header.h>
#include <pistache/mime.h>

#include <iostream>

LeuchtAPI::LeuchtAPI(Address addr, const char* html, const std::vector<std::string>& features)
    : httpEndpoint_(std::make_shared<Http::Endpoint>(addr)),
      html_(html),
      features_(features)
{

}

void LeuchtAPI::init(const std::string& active, size_t threads)
{
    if (std::find(features_.begin(), features_.end(), active) == features_.end()) {
        std::cerr << "Tried to activate unknown feature " << active << std::endl;
    } else {
        active_ = active;
    }

    auto opts = Http::Endpoint::options()
            .threads(threads)
            .flags(Tcp::Options::ReuseAddr);
    httpEndpoint_->init(opts);
    setupRoutes();
}

void LeuchtAPI::start()
{
    httpEndpoint_->setHandler(router_.handler());
    httpEndpoint_->serve();
}

void LeuchtAPI::setupRoutes()
{
    using namespace Rest;

    Routes::Post(router_, "/api/active/:feature?", Routes::bind(&LeuchtAPI::doSetActiveFeature, this));
    Routes::Get(router_, "/api/features", Routes::bind(&LeuchtAPI::doGetFeatures, this));
    Routes::Get(router_, "/api/active", Routes::bind(&LeuchtAPI::doGetActiveFeature, this));
    Routes::Get(router_, "/", Routes::bind(&LeuchtAPI::doGetIndex, this));
}

void LeuchtAPI::doSetActiveFeature(const Rest::Request& request, Http::ResponseWriter response)
{
    std::string feature = request.param(":feature").as<std::string>();

    if (std::find(features_.begin(), features_.end(), feature) == features_.end()) {
        response.send(Http::Code::Not_Found, "Feature \"" + feature + "\" does not exist");
    } else {
        active_ = feature;
        std::cout << "Switched to " << active_ << std::endl;
        response.headers().add<Http::Header::ContentType>(MIME(Text, Plain));
        response.send(Http::Code::Ok, active_);
    }
}

void LeuchtAPI::doGetActiveFeature(const Rest::Request& request, Http::ResponseWriter response)
{
    (void)request;
    response.headers().add<Http::Header::ContentType>(MIME(Text, Plain));
    response.send(Http::Code::Ok, active_);
}

void LeuchtAPI::doGetFeatures(const Rest::Request& request, Http::ResponseWriter response)
{
    (void)request;

    std::string ret("[");
    for (size_t i = 0; i < features_.size(); ++i) {
        ret += '"' + features_[i] + '"';
        if (i + 1 < features_.size())
            ret += ',';
    }
    ret += ']';

    response.headers().add<Http::Header::ContentType>(MIME(Text, Json));
    response.send(Http::Code::Ok, ret);
}

void LeuchtAPI::doGetIndex(const Rest::Request& request, Http::ResponseWriter response)
{
    (void)request;
    response.send(Http::Code::Ok, html_);
}
