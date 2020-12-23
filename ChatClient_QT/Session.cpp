#include "Session.h"

void Session::Run(std::string pIp, std::string pPort, CALLBACKFUNC pCallback)
{
    m_callback = std::move(pCallback);
    m_host = pIp;
    m_resolver.async_resolve(pIp, pPort, beast::bind_front_handler(&Session::OnResolve, shared_from_this()));

    return;
}

void Session::Send(std::string pText)
{
    ptime now = second_clock::local_time();

    pText = "[" + to_simple_string(now) + "] " + pText;

    ptree pt;
    pt.put("message", pText);

    std::stringstream ss;
    write_json(ss, pt, false);
    auto const text = ss.str();

    m_text = text;
    m_ws.async_write(net::buffer(m_text), beast::bind_front_handler(&Session::OnWrite, shared_from_this()));

    return;
}

void Session::Close()
{
    m_ws.async_close(websocket::close_code::normal, beast::bind_front_handler(&Session::OnClose, shared_from_this()));

    return;
}

void Session::OnResolve(beast::error_code pEc, tcp::resolver::results_type results)
{
    if (pEc)
        return m_callback("resolve fail!!");

    beast::get_lowest_layer(m_ws).expires_after(std::chrono::seconds(30));
    beast::get_lowest_layer(m_ws).async_connect(results, beast::bind_front_handler(&Session::OnConnect, shared_from_this()));

    return;
}

void Session::OnConnect(beast::error_code pEc, tcp::resolver::results_type::endpoint_type ep)
{
    if (pEc)
        return m_callback("connect fail!!");

    beast::get_lowest_layer(m_ws).expires_never();
    m_ws.set_option(websocket::stream_base::timeout::suggested(beast::role_type::client));

    m_ws.set_option(
        websocket::stream_base::decorator(
            [](websocket::request_type& req)
            {
                req.set(http::field::user_agent, std::string(BOOST_BEAST_VERSION_STRING) + " ChatClient by SSH");
            }
        )
    );

    m_host += ':' + std::to_string(ep.port());

    m_ws.async_handshake(m_host, "/", beast::bind_front_handler(&Session::OnHandshake, shared_from_this()));

    return;
}

void Session::OnHandshake(beast::error_code pEc)
{
    if (pEc)
        return m_callback("handshake fail!!");

    m_ws.async_read(m_buffer, beast::bind_front_handler(&Session::OnRead, shared_from_this()));

    return;
}

void Session::OnRead(beast::error_code pEc, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (pEc)
        return m_callback("read fail!!");

    std::stringstream ss(beast::buffers_to_string(m_buffer.data()));
    ptree pt;
    read_json(ss, pt);

    auto message = pt.get<std::string>("message");

    m_callback(message);

    m_buffer.clear();

    m_ws.async_read(m_buffer, beast::bind_front_handler(&Session::OnRead, shared_from_this()));

    return;
}

void Session::OnWrite(beast::error_code pEc, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (pEc)
        return m_callback("write fail!!");

    return;
}

void Session::OnClose(beast::error_code pEc)
{
    if (pEc)
        return m_callback("close fail!!");

    return;
}
