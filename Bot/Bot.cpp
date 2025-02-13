 #include "Bot.hpp"
 #include "../Server.hpp"
 #include <sys/socket.h>
 #include <exception>

//--------------------------------------------------------------------------//
//                      - CONSTRUCTORS & DESTRUCTORS -                            //
//--------------------------------------------------------------------------//

Bot::Bot()
{

}

Bot::Bot(int port, char *network, std::string password, int pid) : _port(port), _network(network), _password(password), _pidServ(pid)
{
    kill(_pidServ, SIGUSR1);
}

Bot::Bot(Bot const &bot)
{
    *this = bot;
}

Bot::~Bot()
{

}


//--------------------------------------------------------------------------//
//                               - OPERATORS -                                    //
//--------------------------------------------------------------------------//

Bot    &Bot::operator=(Bot const &bot)
{
    (void)bot;
    return (*this);
}


//--------------------------------------------------------------------------//
//                           - GETTERS & SETTERS -                                //
//--------------------------------------------------------------------------//


//--------------------------------------------------------------------------//
//                           - MEMBER FUNCTIONS -                                //
//--------------------------------------------------------------------------//
void    Bot::bot_init(const char *network, int port)
{
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);
    (void)network;
    (void)port;

    if((_socket = socket(AF_INET, SOCK_STREAM, 0) < 0))
        throw std::runtime_error("Error while opening a socket!");
    int up = connect(_socket, (sockaddr *) &addr, size);

    fcntl(_socket, F_SETFL, O_NONBLOCK);
    (void)up;
    std::string register_message = "PASS " + _password + "\r\n" +
                          "NICK " + "Meteosaurus" + "\r\n" +
                          "USER " + "Meteosaurus 1 Robometeo bot\r\n";
}