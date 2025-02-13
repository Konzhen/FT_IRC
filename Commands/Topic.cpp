#include "../Command.hpp"

Topic::Topic(Server* srv) : Command(srv) 
{

}

Topic::~Topic() 
{

}

void    Topic::execute(Client* client, std::vector<std::string> args)
{

    if (args.size() < 1 || args[0].empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "TOPIC"));
        return;
    }
    std::string target = args.at(0);
    Channel *channel = _srv->get_channel(target);

    if (!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), target));
        return;
    }

    if (args.size() == 1)
    {
        client->reply(channel->get_topic());
        return;
    }

    if (channel->get_oponly() && channel->get_admin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), target));
        return;
    }

    std::string topic;
    std::vector<std::string>::iterator it = args.begin() + 1;
    std::vector<std::string>::iterator end = args.end();

    while (it != end)
    {
        topic.append(*it + " ");
        it++;
    }
    channel->set_topic(topic);
}