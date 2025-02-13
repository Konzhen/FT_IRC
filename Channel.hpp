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
    std::string             _topic;
    Client*                 _admin;
    std::vector<Client *>   _clients;
    std::string             _k;
    size_t                  _l;
    bool                    _n;
    bool                    _i;
    bool                    _o;

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

    // Getters & Setters-
    std::string                 get_name() const;
    std::string                 get_topic() const;
    void                        set_topic(std::string topic);
    bool                        get_oponly() const;
    void                        set_oponly(bool oponly);
    bool                        get_invite() const;
    void                        set_invite(bool invite);
    Client*                     get_admin() const;
    void                        set_admin(Client *user);
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
    void                        invite(Client* client, Client* target);

};

#endif