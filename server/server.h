#pragma once
#include <iostream>
#include "session.h"
#include "common/command.h"

using thread_pool = std::vector<std::thread>;


class Server
{
public:
    Server(short i_port, Led &i_led) :
        io_context(),
        strand(io_context),
        signals(io_context),
        acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), i_port)),
        led(i_led)
    {
        doAccept();
        signals.add(SIGINT);
        signals.async_wait(std::bind(&Server::stop, this));
    }

    void run()
    {
        workerThreadPool();
    }

    void stop()
    {
        io_context.stop();
    }

private:
    void doAccept()
    {
        auto h = [this](boost::system::error_code ec, boost::asio::ip::tcp::socket socket)
        {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket), strand, led)->start();
            }

            doAccept();
        };

        acceptor.async_accept(h);
    }

    void workerThreadPool()
    {
        int n = std::thread::hardware_concurrency();
        n = n > 0 ? n : 1;
        thread_pool thread_pool_;
        thread_pool_.reserve(n);

        for (int i = 0; i != n; i++)
        {
            thread_pool_.push_back(std::thread([this]() {worker(); }));
        }

        for (int i = 0; i != n; i++)
        {
            thread_pool_[i].join();
        }
    }

    void worker()
    {
        while (true)
        {
            try
            {
                io_context.run();
                break;
            }
            catch (std::exception& e)
            {
                std::cerr << "Exception: " << e.what() << "\n";
            }
            catch (...)
            {
                std::cout << "Exception in worker" << "\n";
            }
        }
    }


    boost::asio::io_context io_context;
    boost::asio::io_service::strand strand;
    boost::asio::signal_set signals;
    boost::asio::ip::tcp::acceptor acceptor;
    Led& led;

    std::vector<std::shared_ptr<Session>> sessions;
};