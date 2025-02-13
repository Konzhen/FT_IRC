#ifndef CLIENT_HPP
#define CLIENT_HPP

//--------------------------------------------------------------------------//
//    -                           - INCLUDES -                                -    //
//--------------------------------------------------------------------------//

class Client;

# include <iostream>
# include <sys/socket.h>
# include <sys/poll.h>
# include <string>
# include <vector>
# include "Channel.hpp"
# include "Response.hpp"

enum ClientState
{
    HANDSHAKE,
    LOGIN,
    REGISTERED,
    DISCONNECTED
};

//--------------------------------------------------------------------------//
//                                 - CLASS -                                    //
//--------------------------------------------------------------------------//

class Client
{
//--PRIVATE-----------------------------------------------------------------//
    private:
                           // - VARIABLES - //
    int             _fd;
    int             _port;
    std::string     _nickname;
    std::string     _username;
    std::string     _realname;
    std::string     _hostname;

    ClientState     _state;
    Channel*        _channel;
                           // - FUNCTIONS - //

    // Constructor & Destructors


    // Operators


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
    Client();
    Client(int fd, int port, const std::string &hostname);
    Client(Client const &client);
    ~Client();

    // Operators
    Client &operator=(Client const &client);

    // Getters & Setters
    int             get_fd() const;
    int             get_port() const;
    std::string     get_nickname() const;
    std::string     get_username() const;
    std::string     get_realname() const;
    std::string     get_hostname() const;
    std::string     get_prefix() const;
    Channel*        get_channel() const;
    void            set_nickname(const std::string &nickname);
    void            set_username(const std::string &username);
    void            set_realname(const std::string &realname);
    void            set_state(ClientState state);
    void            set_channel(Channel *channel);

    // Member Functions
    bool            is_registered() const;
    void            write(const std::string& message) const;
    void            reply(const std::string& reply);
    void            welcome();
    void            goodbye();
    void            join(Channel *channel);
    void            leave();

};

#endif