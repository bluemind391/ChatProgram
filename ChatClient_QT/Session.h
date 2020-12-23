#pragma once

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <memory>
#include <functional>

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;
using namespace boost::json;
using namespace boost::property_tree::json_parser;
using namespace boost::posix_time;
using boost::property_tree::ptree;

typedef std::function<void(std::string)> CALLBACKFUNC;

class Session : public std::enable_shared_from_this<Session>
{

public:
    explicit Session(net::io_context& ioc) : m_resolver(net::make_strand(ioc)), m_ws(net::make_strand(ioc))
    {
    }

    void Run(std::string pIp, std::string pPort, CALLBACKFUNC pCallback);
    void Send(std::string pText);
    void Close();

private:
    CALLBACKFUNC m_callback;
    tcp::resolver m_resolver;
    websocket::stream<beast::tcp_stream> m_ws;
    beast::flat_buffer m_buffer;
    std::string m_host;
    std::string m_text;

    void OnResolve(beast::error_code pEc, tcp::resolver::results_type pResults);
    void OnConnect(beast::error_code pEc, tcp::resolver::results_type::endpoint_type pEp);
    void OnHandshake(beast::error_code pEc);
    void OnRead(beast::error_code pEc, std::size_t pBytes_transferred);
    void OnWrite(beast::error_code pEc, std::size_t pBytes_transferred);
    void OnClose(beast::error_code pEc);
};

