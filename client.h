//
// Created by matt on 3/20/16.
//

#ifndef CPE4097_CLIENT_H
#define CPE4097_CLIENT_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <vector>
#include "connection.hpp"
#include <boost/serialization/vector.hpp>
#include "Joystick.h"

class Client
{
    public:
        Client(boost::asio::io_service& io_service, const std::string& host, const std::string& service);

        void handle_connect(const boost::system::error_code &e,
                            boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

        void handle_read(const boost::system::error_code &e);

        void read(const boost::system::error_code& e);

    private:
        boost::asio::deadline_timer timeout;

        connection c;

        Joystick::joystick_state joystick;
};


#endif //CPE4097_CLIENT_H
