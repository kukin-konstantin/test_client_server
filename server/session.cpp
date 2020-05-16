#include "session.h"
#include <iostream>

Session::Session(boost::asio::ip::tcp::socket i_socket, boost::asio::io_service::strand& i_strand, Led& i_led)
    : socket(std::move(i_socket)),
        strand(i_strand),
        led(i_led)
{
}

void Session::start()
{
    doRead();
}

void Session::doRead()
{
    auto self(shared_from_this());
    auto h = [this, self](boost::system::error_code ec, std::size_t length)
    {
        if (!ec)
        {
            strcpy(data_out, parse(data_in, led).c_str());
            std::fill(&data_in[0], &data_in[0] + max_length, 0);
            doWrite();
        }
    };
    socket.async_read_some(boost::asio::buffer(data_in, max_length), boost::asio::bind_executor(strand, h));
}

void Session::doWrite()
{
    auto self(shared_from_this());
    boost::asio::async_write(socket, boost::asio::buffer(data_out, max_length),
        [this, self](boost::system::error_code ec, std::size_t)
        {
            if (!ec)
            {
                std::fill(&data_out[0], &data_out[0] + max_length, 0);
                doRead();
            }
        });
}
