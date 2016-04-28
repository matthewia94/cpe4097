/* 
 * File:   main.cpp
 * Author: Sam
 *         Matt 
 *
 * Created on February 10, 2016, 6:31 PM
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "client.h"

using std::cout;
using std::endl;
using std::endl;

int main(int argc, char** argv)
{
    try
    {
        // Check command line arguments.
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_service io;
        Client c(io, argv[1], argv[2]);
        io.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
