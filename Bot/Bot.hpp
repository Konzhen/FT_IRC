#ifndef BOT_HPP
#define BOT_HPP

//--------------------------------------------------------------------------//
//    -                           - INCLUDES -                                -    //
//--------------------------------------------------------------------------//

# include <iostream>

//--------------------------------------------------------------------------//
//                                 - CLASS -                                    //
//--------------------------------------------------------------------------//

class Bot
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
    int _port;
    char *_network;
    std::string _password;
    int _socket;
    int _pidServ;

                           // - FUNCTIONS - //

    // Constructor & Destructors
    Bot();
    Bot(int port, char *network, std::string password, int pid);
    Bot(Bot const &bot);
    ~Bot();


    // Operators
    Bot &operator=(Bot const &bot);

    // Getters & Setters


    // Member Functions
    void bot_init(const char *network, int port);
};

#endif