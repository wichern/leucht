#ifndef __LEUCHT_LEUCHTAPI_H__
#define __LEUCHT_LEUCHTAPI_H__

#include <pistache/endpoint.h>
#include <pistache/net.h>
#include <pistache/router.h>

#include <string>
#include <vector>
#include <map>

using namespace Pistache;

struct LeuchtAPI
{
public:
    LeuchtAPI(Address addr, const char* html, const std::vector<std::string>& features);

    void init(const std::string& active, size_t threads = 1);
    void start();

private:
    void setupRoutes();

    void doSetActiveFeature(const Rest::Request& request, Http::ResponseWriter response);
    void doGetActiveFeature(const Rest::Request& request, Http::ResponseWriter response);
    void doGetFeatures(const Rest::Request& request, Http::ResponseWriter response);
    void doGetIndex(const Rest::Request& request, Http::ResponseWriter response);

    const char* html_;
    std::shared_ptr<Http::Endpoint> httpEndpoint_;
    Rest::Router router_;

    std::string active_;
    const std::vector<std::string> features_;
};

#endif  // __LEUCHT_LEUCHTAPI_H__
