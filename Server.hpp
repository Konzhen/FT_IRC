#ifndef SERVER_HPP
#define SERVER_HPP

//--------------------------------------------------------------------------//
//    -                           - INCLUDES -                                -    //
//--------------------------------------------------------------------------//

class Server;

# include <iostream>
# include <sys/socket.h>
# include <sys/poll.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <poll.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <csignal>
# include <stdexcept>
# include <cerrno>
# include <string>
# include <algorithm>
# include <vector>
# include <map>
# include "Client.hpp"
# include "Channel.hpp"
# include "Parser.hpp"

//--------------------------------------------------------------------------//
//                                 - CLASS -                                    //
//--------------------------------------------------------------------------//
#define MAX_CONNECTIONS 200

class Server
{
typedef std::vector<Channel *>::iterator    channel_iterator;
typedef std::map<int, Client *>::iterator   client_iterator;

//--PRIVATE-----------------------------------------------------------------//
    private:
                           // - VARIABLES - //
    bool                    _dc;
    int                     _running;
    int                     _sock;
    int                     _size;
    const std::string       _host;
    const std::string       _port;
    const std::string       _pass;
    struct pollfd           _pfds[MAX_CONNECTIONS];
    std::vector<Channel *>  _channels;
    std::map<int, Client *> _clients;
    Parser*                 _parser;
    sig_atomic_t*           _stopRequest;
    sig_atomic_t*           _botStatus;

                           // - FUNCTIONS - //

    // Constructor & Destructors

    // Signal Handlers

    // Getters & Setters


    // Member Functions


//--PROTECTED---------------------------------------------------------------//
    protected:
                           // - VARIABLES - //



                           // - FUNCTIONS - //

    // Constructor & Destructors


    // Operators


    // Getters & Setters


    // Member Functions


//--PUBLIC------------------------------------------------------------------//
    public:
                           // - VARIABLES - //


                           // - FUNCTIONS - //

    // Constructor & Destructors
        Server();
        Server(const std::string &port, const std::string &pass);
        Server(Server const &server);
        ~Server();


    // Operators
        Server &operator=(Server const &server);

    // Getters & Setters
        std::string     get_password() const;
        Client*         get_client(const std::string &nickname);
        Channel*        get_channel(const std::string &name);
        sig_atomic_t*   get_botStatus();
        void            set_stop(sig_atomic_t* stop);
        void            set_bot(sig_atomic_t* bot);

    // Member Functions
    void            start();
    void            on_client_connect();
    void            on_client_disconnect(int fd);
    void            on_client_message(int fd);
    void            say_goodbye();
    std::string     read_message(int fd);
    Channel*        create_channel(const std::string &name, const std::string &key, Client *client);
    int             create_socket();
};

#endif