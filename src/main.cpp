#include <iostream>
#include "httplib.h"
#include <json.hpp> // You need to install the nlohmann/json library

using json = nlohmann::json;

int main() {
    // Create an httplib client instance
    httplib::Client cli("httpbin.org");

    // // Create JSON data
    // json data = {{"hii", "hello"}};

    // // Make a POST request with JSON data
    // httplib::Headers headers = {{"Content-Type", "application/json"}};
    auto res = cli.Get("/image");

    if (res && res->status == 200) {
        std::cout << "Response body: " << res->body << std::endl;
    } else {
        std::cerr << "Error: " << (res ? res->status : -1) << std::endl;
    }

    return 0;
}
