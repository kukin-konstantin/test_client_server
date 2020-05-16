#pragma once
#include <boost/asio.hpp>
#include "common/command.h"


class Session
    : public std::enable_shared_from_this<Session>
{
public:
    Session(boost::asio::ip::tcp::socket i_socket, boost::asio::io_service::strand& i_strand,
        Led& i_led);

    void start();

private:
    void doRead();

    void doWrite();

    boost::asio::ip::tcp::socket socket;
    boost::asio::io_service::strand& strand;
    Led& led;

    enum { max_length = 32 };
    char data_in[max_length];
    char data_out[max_length];
};
