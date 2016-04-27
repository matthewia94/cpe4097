//
// Created by matt on 3/20/16.
//

#include "client.h"

using boost::asio::ip::tcp;

Client::Client(boost::asio::io_service& io_service, const std::string& host, const std::string& service)
        : c(io_service), timeout(io_service)
{
    // Resolve the host name into an IP address.
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(tcp::v4(), host, service);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    tcp::endpoint endpoint = *resolver.resolve(query);

    // Start an asynchronous connect operation.
    c.socket().async_connect(endpoint, boost::bind(&Client::handle_connect, this,
                                                             boost::asio::placeholders::error, ++endpoint_iterator));
}

void Client::handle_connect(const boost::system::error_code& e,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
{
    if (!e)
    {
        c.async_read(joystick, boost::bind(&Client::handle_read, this, boost::asio::placeholders::error));
    }
    else if (endpoint_iterator != boost::asio::ip::tcp::resolver::iterator())
    {
        c.socket().close();
        boost::asio::ip::tcp::endpoint endpoint = *endpoint_iterator;
        c.socket().async_connect(endpoint, boost::bind(&Client::handle_connect, this,
                                                       boost::asio::placeholders::error, ++endpoint_iterator));
    }
    else
    {
        // An error occurred. Log it and return. Since we are not starting a new
        // operation the io_service will run out of work to do and the client will
        // exit.
        std::cerr << e.message() << std::endl;
    }
}

void Client::handle_read(const boost::system::error_code& e)
{
    if (!e)
    {
        // Print out the data that was received.
        std::cout << "  Axes: " << joystick.num_axes << "\n";
        for(std::size_t j = 0; j < joystick.num_axes; j++)
        {
            std::cout << "Axis " << j << " : " << joystick.axis[j] << std::endl;
        }
        std::cout << "  Buttons: " << joystick.num_buttons << "\n";
        for(std::size_t j = 0; j < joystick.num_buttons; j++)
        {
            std::cout << "Button " << j << " : " << joystick.button[j] << std::endl;
        }

        timeout.expires_from_now(boost::posix_time::seconds(1));
        timeout.async_wait(boost::bind(&Client::read, this, boost::asio::placeholders::error));
    }
    else
    {
        // An error occurred.
        std::cerr << e.message() << std::endl;
    }
}

void Client::read(const boost::system::error_code& e)
{
    c.async_read(joystick, boost::bind(&Client::handle_read, this, boost::asio::placeholders::error));
}