#ifndef CHANNEL_HPP
#define CHANNEL_HPP

//--------------------------------------------------------------------------//
//    -                           - INCLUDES -                                -    //
//--------------------------------------------------------------------------//

class Channel;

# include <iostream>
# include "Server.hpp"
# include "Client.hpp"
# include "Response.hpp"

//--------------------------------------------------------------------------//
//                                 - CLASS -                                    //
//--------------------------------------------------------------------------//

class Channel
{
typedef std::vector<Client *>::iterator client_iterator;
//--PRIVATE-----------------------------------------------------------------//
    private:
                           // - VARIABLES - //
    std::string             _name;
    Client*                 _admin;
    std::vector<Client *>   _clients;
    std::string             _k;
    size_t                  _l;
    bool                    _n;

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
    Channel();
    Channel(const std::string &name, const std::string &key, Client* admin);
    Channel(Channel const &channel);
    ~Channel();


    // Operators
    Channel &operator=(Channel const &channel);

    // Getters & Setters
    std::string                 get_name() const;
    Client*                     get_admin() const;
    std::string                 get_key() const;
    void                        set_key(std::string key);
    size_t                      get_limit() const;
    void                        set_limit(size_t limit);
    bool                        ext_msg() const;
    void                        set_ext_msg(bool flag);
    size_t                      get_size() const;
    std::vector<std::string>    get_nicknames();

    // Member Functions
    void                        broadcast(const std::string& message);
    void                        broadcast(const std::string& message, Client* exclude);
    void                        add_client(Client* client);
    void                        remove_client(Client* client);
    void                        kick(Client* client, Client* target, const std::string& reason);

};

#endif