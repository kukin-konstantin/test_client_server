#pragma once
#include <iostream>
#include <thread>
#include <boost/asio.hpp>


class Client
{
public:
    Client(std::string && i_host, std::string &&i_port):
        io_context(),
        work(io_context),
        socket(io_context),
        resolver(io_context),
        host(std::move(i_host)),
        port(std::move(i_port))
    {
        std::thread t_tmp([this]() {
            io_context.run();
            });
        th.swap(t_tmp);
    }

    virtual ~Client()
    {
        io_context.stop();
        th.join();
        close();
    }

    std::string doCommand(const std::string& request)
    {
        if (write(request))
        {
            auto result = read();
            return result;
        }
        return "FAILED error in write\n";
    }

    bool connect()
    {
        boost::system::error_code er;
        boost::asio::connect(socket, resolver.resolve(host, port), er);
        if (er)
        {
            std::cout << "error connect " << er.message()<<"\n";
        }
        return !er;
    }

private:
    
    bool write(const std::string& data)
    {
        boost::system::error_code er;
        boost::asio::write(socket, boost::asio::buffer(data, data.size()), er);
        if (er)
        {
            std::cout << "error write " << er.message() << "\n";
        }
        return !er;
    }

    std::string read()
    {
        boost::system::error_code er;
        boost::asio::read_until(socket, buffer, "\n");
        auto data = buffer.data();
        std::string s_data(boost::asio::buffers_begin(data),
            boost::asio::buffers_begin(data) + buffer.size());

        s_data = std::string(s_data.begin(), s_data.begin()+s_data.find('\n')+1);

        buffer.consume(buffer.size());
        if (er)
        {
            std::cout << "error read " << er.message() << "\n";
            return "FAILED " + er.message() + "\n";
        }
        return s_data;
    }

    void close()
    {
        boost::system::error_code er;
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, er);
        if (er)
        {
            std::cout << "error close " << er.message() << "\n";
        }
    }


private:
    boost::asio::io_context io_context;
    boost::asio::io_service::work work;
    boost::asio::ip::tcp::socket socket;
    boost::asio::ip::tcp::resolver resolver;
    std::string host;
    std::string port;
    std::thread th;
    boost::asio::streambuf buffer;
};
