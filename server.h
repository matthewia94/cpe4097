//
// Created by matt on 3/20/16.
//

#ifndef CPE4097_UDP_SERVER_H
#define CPE4097_UDP_SERVER_H


#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp"
#include <boost/serialization/vector.hpp>
#include "Joystick.h"

using boost::asio::ip::udp;

class Server
{
    public:
        /// Constructor opens the acceptor and starts waiting for the first incoming
        /// connection.
        Server(boost::asio::io_service& io_service, unsigned short port);

        ~Server();

        static void* loop(void *obj);

        void deliver();

        /// Handle completion of a accept operation.
        void handle_accept(const boost::system::error_code& e, connection_ptr conn);

        /// Handle completion of a write operation.
        void handle_write(const boost::system::error_code& e, connection_ptr conn);

        void send(const boost::system::error_code& error);

    private:
        /// The acceptor object used to accept incoming socket connections.
        boost::asio::ip::tcp::acceptor acceptor;

        /// The data to be sent to each client.
        Joystick joystick;

        connection_ptr conn;

        boost::asio::deadline_timer timer;

        bool is_running;
};


#endif //CPE4097_UDP_SERVER_H
