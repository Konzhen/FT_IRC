#ifndef COMMAND_HPP
#define COMMAND_HPP

//--------------------------------------------------------------------------//
//    -                           - INCLUDES -                                -    //
//--------------------------------------------------------------------------//

class Command;

# include <iostream>
# include <numeric>
# include <string>
# include "Server.hpp"
//--------------------------------------------------------------------------//
//                                 - CLASS -                                    //
//--------------------------------------------------------------------------//

class Command
{
//--PRIVATE-----------------------------------------------------------------//
    private:
                           // - VARIABLES - //



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
        Server* _srv;
        bool    _auth;
                           // - FUNCTIONS - //

    // Constructor & Destructors
        Command();
        Command(Command const &command);
        explicit Command(Server* srv, bool auth = true);
        virtual ~Command();


    // Operators
        Command &operator=(Command const &command);

    // Getters & Setters


    // Member Functions
    bool auth_required() const;
    virtual void execute(Client* client, std::vector<std::string> args) = 0;
};

class Notice : public Command
{
    public:

        Notice(Server* srv);
        ~Notice();

        void    execute(Client* client, std::vector<std::string> args);
};

class PrivMsg : public Command
{
    public:

        PrivMsg(Server* srv);
        ~PrivMsg();

        void    execute(Client* client, std::vector<std::string> args);
};

class Part : public Command
{
    public:

        Part(Server* srv);
        ~Part();

        void    execute(Client* client, std::vector<std::string> args);
};

class Quit : public Command
{
    public:

        Quit(Server* srv, bool auth);
        ~Quit();

        void    execute(Client* client, std::vector<std::string> args);
};

class Join : public Command
{
    public:

        Join(Server* srv);
        ~Join();

        void    execute(Client* client, std::vector<std::string> args);
};

class User : public Command
{
    public:

        User(Server* srvi, bool auth);
        ~User();

        void    execute(Client* client, std::vector<std::string> args);
};

class Nick : public Command
{
    public:

        Nick(Server* srv, bool auth);
        ~Nick();

        void    execute(Client* client, std::vector<std::string> args);
};

class Pass : public Command
{
    public:

        Pass(Server* srv, bool auth);
        ~Pass();

        void    execute(Client* client, std::vector<std::string> args);
};

class Kick : public Command
{
    public:

        Kick(Server* srv);
        ~Kick();

        void    execute(Client* client, std::vector<std::string> args);
};

class Ping : public Command
{
    public:

        Ping(Server* srv);
        ~Ping();

        void    execute(Client* client, std::vector<std::string> args);
};

class Pong : public Command
{
    public:

        Pong(Server* srv);
        ~Pong();

        void    execute(Client* client, std::vector<std::string> args);
};

class Mode : public Command
{
    public:

        Mode(Server* srv);
        ~Mode();

        void    execute(Client* client, std::vector<std::string> args);
};

class Meteo : public Command
{
    public:

        Meteo(Server* srv);
        ~Meteo();

        void    execute(Client* client, std::vector<std::string> args);
};

class Invite : public Command
{
    public:

        Invite(Server* srv);
        ~Invite();

        void    execute(Client* client, std::vector<std::string> args);
};

class Topic : public Command
{
    public:

        Topic(Server* srv);
        ~Topic();

        void    execute(Client* client, std::vector<std::string> args);
};

#endif