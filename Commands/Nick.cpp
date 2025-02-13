#include "../Command.hpp"

Nick::Nick(Server* srv, bool auth) : Command(srv, auth) 
{

}

Nick::~Nick() 
{

}

void    Nick::execute(Client* client, std::vector<std::string> args)
{
    if (args.empty() || args[0].empty()) 
    {
        client->reply(ERR_NONICKNAMEGIVEN(client->get_nickname()));
        return;
    }
    std::string nickname = args[0];
    if (_srv->get_client(nickname))
    {
        client->reply(ERR_NICKNAMEINUSE(client->get_nickname()));
        return;
    }
    client->set_nickname(nickname);
    client->welcome();
}
