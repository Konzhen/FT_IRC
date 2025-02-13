#include "../Command.hpp"

Invite::Invite(Server* srv) : Command(srv) 
{
    
}

Invite::~Invite() 
{
    
}

void    Invite::execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2)
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "INVITE"));
        return;
    }
    std::string name = args[0];
    std::string target = args[1];
    Channel *channel = client->get_channel();
    if (!channel || channel->get_name() != name)
    {
        client->reply(ERR_NOTONCHANNEL(client->get_nickname(), name));
        return;
    }
    if (channel->get_admin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), name));
        return;
    }
    Client *dest = _srv->get_client(target);
    if (!dest)
    {
        client->reply(ERR_NOSUCHNICK(client->get_nickname(), target));
        return;
    }
    if (dest->get_channel() || dest->get_channel() == channel)
    {
        client->reply(ERR_USERALREADYINCHANNEL(client->get_nickname(), dest->get_nickname(), name));
        return;
    }
	channel->invite(client, dest);
    dest->join(channel);
}