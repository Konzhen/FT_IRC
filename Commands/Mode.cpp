#include "../Command.hpp"

Mode::Mode(Server* srv) : Command(srv) 
{

}

Mode::~Mode() 
{

}

void    Mode::execute(Client* client, std::vector<std::string> args)
{
    if (args.size() < 2 || args[1].size() < 2 || (args[1][0] != '-' && args[1][0] != '+'))
    {
        client->reply(ERR_NEEDMOREPARAMS(client->get_nickname(), "MODE"));
        return;
    }

    std::string target = args.at(0);
    Channel *channel = _srv->get_channel(target);
    if (!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->get_nickname(), target));
        return;
    }

    if (channel->get_admin() != client)
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->get_nickname(), target));
        return;
    }
	int i = 0;
    int p = 2;
	char c;
    
    while ((c = args[1][i]))
    {
        char prev_c = i > 0 ? args[1][i - 1] : '\0';
        bool active = prev_c == '+';
        switch (c) 
        {
            case 'n':
            {
                channel->set_ext_msg(active);
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+n" : "-n"), ""));
                break;
            }
			case 'l':
            {
                if(prev_c == '+' && args.size() == 2)
                {
                    client->reply("You need to specify a channel users limit");
                    break;
                }
                channel->set_limit(active ? atoi(args[p].c_str()) : 0);
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+l" : "-l"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
			case 'k':
            {
                if (prev_c == '-')
                {
                    channel->set_key("");
                    break;
                }
                if(prev_c == '+' && args.size() == 2)
                {
                    client->reply("You need to specify a channel key");
                    break;
                }
                channel->set_key(args[p]);
                channel->broadcast(RPL_MODE(client->get_prefix(), channel->get_name(), (active ? "+k" : "-k"), (active ? args[p] : "")));
                p += active ? 1 : 0;
                break;
            }
            case 't':
            {
                channel->set_oponly(active);
                channel->broadcast("Topic mode has been changed.");
                p += active ? 1 : 0;
                break;
            }
            case 'i':
            {
                channel->set_invite(active);
                channel->broadcast("Channel mode has been changed.");
                p += active ? 1 : 0;
                break;
            }
            case 'o':
            {
                if(args.size() != 3)
                {
                    client->reply("You need to specify a target");
                    break;
                }
                if(args[1].at(0) == '-')
                {
                    channel->set_admin(NULL);
                    client->reply("Admin privilegdes lost");
                    return ;
                }
                std::vector<std::string> nicknames = channel->get_nicknames();
                for (size_t i = 0; i<nicknames.size(); i++)
                {
                    if (args.at(2) == nicknames.at(i))
                    {
                        channel->set_admin(_srv->get_client(args.at(2)));
                        _srv->get_client(args.at(2))->reply("Admin privilidges granted");
                        p += active ? 1 : 0;
                        return;
                    }
                }
                break;
            }
            default:
            break;
        }
        i++;
    }
}
