#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <boost/beast.hpp>
#include <boost/asio/ssl.hpp>
#include "json.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;
using json = nlohmann::json;

std::vector<std::string> email_domains = {"@outlook.fr", "@outlook.com", "@gmail.com", "@protonmail.com", "@yahoo.com", "@hotmail.com"};
std::vector<std::string> gender = {"1", "2"};

json config;

std::string getYear() {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    int year = timeinfo->tm_year + 1900;
    return std::to_string(year);
}

std::string generateEmail() {
    return "example" + std::to_string(rand() % 1000) + email_domains[rand() % email_domains.size()];
}

std::string generateUserName() {
    return "user" + std::to_string(rand() % 1000);
}

void Gen() {
    std::string birth_date = getYear() + "-11-02";
    std::string email_val = generateEmail();
    std::string user_name = generateUserName();
    std::string gender_val = gender[rand() % gender.size()];

    json payload;
    payload["account_details"]["birthdate"] = birth_date;
    payload["account_details"]["consent_flags"]["eula_agreed"] = true;
    payload["account_details"]["consent_flags"]["send_email"] = true;
    payload["account_details"]["consent_flags"]["third_party_email"] = false;
    payload["account_details"]["display_name"] = user_name;
    payload["account_details"]["email_and_password_identifier"]["email"] = email_val;
    payload["account_details"]["email_and_password_identifier"]["password"] = "amrxtdaddy";
    payload["account_details"]["gender"] = gender_val;
    payload["callback_uri"] = "https://www.spotify.com/signup/challenge?locale=in-en";
    payload["client_info"]["api_key"] = "a1e486e2729f46d6bb368d6b2bcda326";
    payload["client_info"]["app_version"] = "v2";
    payload["client_info"]["capabilities"].push_back(1);
    payload["client_info"]["installation_id"] = "fc1e5e8c-1482-450e-b6f3-bd880944c1f3";
    payload["client_info"]["platform"] = "www";
    payload["tracking"]["creation_flow"] = "";
    payload["tracking"]["creation_point"] = "https://www.spotify.com/in-en/free/?utm_source=in-en_brand_contextual_text&utm_medium=paidsearch&utm_campaign=alwayson_asia_in_premiumbusiness_core_brand_neev+contextual+in-en+google";
    payload["tracking"]["referrer"] = "";

    beast::error_code ec;

    net::io_context ioc;
    ssl::context ctx(ssl::context::tlsv12_client);
    ctx.set_default_verify_paths();

    tcp::resolver resolver(ioc);
    ssl::stream<tcp::socket> stream(ioc, ctx);

    auto const results = resolver.resolve("spclient.wg.spotify.com", "https", ec);
    if (ec) {
        std::cerr << "resolve: " << ec.message() << "\n";
        return;
    }

    net::connect(stream.next_layer(), results.begin(), results.end(), ec);
    if (ec) {
        std::cerr << "connect: " << ec.message() << "\n";
        return;
    }

    stream.handshake(ssl::stream_base::client, ec);
    if (ec) {
        std::cerr << "handshake: " << ec.message() << "\n";
        return;
    }

    http::request<http::string_body> req(http::verb::post, "/signup/public/v2/account/create", 11);
    req.set(http::field::host, "spclient.wg.spotify.com");
    req.set(http::field::user_agent, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.0.0 Safari/537.36");
    req.set(http::field::content_type, "application/json");

    req.content_length(payload.dump().size());
    req.body() = payload.dump();

    http::write(stream, req, ec);
    if (ec) {
        std::cerr << "write: " << ec.message() << "\n";
        return;
    }

    beast::flat_buffer buffer;
    http::response<http::string_body> res;

    http::read(stream, buffer, res, ec);
    if (ec) {
        std::cerr << "read: " << ec.message() << "\n";
        return;
    }

    std::cout << res << std::endl;

    stream.shutdown(ec);
    if (ec == net::error::eof) {
        ec.assign(0, ec.category());
    }
    if (ec) {
        std::cerr << "shutdown: " << ec.message() << "\n";
        return;
    }
}

int main() {
    std::srand(std::time(nullptr));

    int threadCount;
    std::cout << "Number of Threads[>] ";
    std::cin >> threadCount;

    for (int i = 0; i < threadCount; ++i) {
        std::thread t(Gen);
        t.detach();
    }

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
