 #include "Command.hpp"

//--------------------------------------------------------------------------//
//                      - CONSTRUCTORS & DESTRUCTORS -                            //
//--------------------------------------------------------------------------//

Command::Command()
{

}

Command::Command(Server* srv, bool auth) :_srv(srv), _auth(auth)
{
    
}

Command::Command(Command const &command)
{

    *this = command;
}

Command::~Command()
{

}


//--------------------------------------------------------------------------//
//                               - OPERATORS -                                    //
//--------------------------------------------------------------------------//

Command    &Command::operator=(Command const &command)
{    
    (void)command;
    return (*this);
}


//--------------------------------------------------------------------------//
//                           - GETTERS & SETTERS -                                //
//--------------------------------------------------------------------------//

bool    Command::auth_required() const 
{
    return (_auth); 
}

//--------------------------------------------------------------------------//
//                           - MEMBER FUNCTIONS -                                //
//--------------------------------------------------------------------------//