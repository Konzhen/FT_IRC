#ifndef PARSER_HPP
#define PARSER_HPP

//--------------------------------------------------------------------------//
//    -                           - INCLUDES -                                -    //
//--------------------------------------------------------------------------//

class Parser;

# include <iostream>
# include <sstream>
# include <string>
# include <vector>
# include <map>
# include "Command.hpp"

//--------------------------------------------------------------------------//
//                                 - CLASS -                                    //
//--------------------------------------------------------------------------//

class Parser
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
    Server*                             _srv;
    std::map<std::string, Command *>    _commands;


                           // - FUNCTIONS - //

    // Constructor & Destructors
    Parser();
    Parser(Server* srv);
    Parser(Parser const &parser);
    ~Parser();


    // Operators
        Parser &operator=(Parser const &parser);

    // Getters & Setters


    // Member Functions
    void            invoke(Client* client, const std::string& message);
    std::string     trim(const std::string& str);
};

#endif