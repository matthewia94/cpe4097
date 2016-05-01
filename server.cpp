//
// Created by matt on 3/20/16.
//

#include "server.h"

Server::Server(boost::asio::io_service& io_service, unsigned short port) :
    acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
    conn(new connection(acceptor.get_io_service())),
    timer(io_service)
{
    // Start an accept operation for a new connection.
    acceptor.async_accept(conn->socket(),
            boost::bind(&Server::handle_accept, this,
                        boost::asio::placeholders::error, conn));

    Joystick::joystick_state js;

    is_running = true;
}

Server::~Server()
{
    is_running = false;
}

void Server::handle_write(const boost::system::error_code& e, connection_ptr conn)
{
    timer.expires_from_now(boost::posix_time::seconds(.1));
    timer.async_wait(boost::bind(&Server::send, this, boost::asio::placeholders::error));
}

void Server::send(const boost::system::error_code& error)
{
    conn->async_write(joystick.joystick_st, boost::bind(&Server::handle_write, this, boost::asio::placeholders::error,
                                                        conn));
}

void Server::handle_accept(const boost::system::error_code& e, connection_ptr conn)
{
    if (!e)
    {
        // Successfully accepted a new connection. Send the list of stocks to the
        // client. The connection::async_write() function will automatically
        // serialize the data structure for us.
        conn->async_write(joystick.joystick_st, boost::bind(&Server::handle_write, this, boost::asio::placeholders::error,
                                                            conn));

        // Start an accept operation for a new connection.
        connection_ptr new_conn(new connection(acceptor.get_io_service()));
        acceptor.async_accept(new_conn->socket(), boost::bind(&Server::handle_accept, this,
                                                              boost::asio::placeholders::error, new_conn));

    }
    else
    {
        // An error occurred. Log it and return. Since we are not starting a new
        // accept operation the io_service will run out of work to do and the
        // server will exit.
        std::cerr << e.message() << std::endl;
    }
}