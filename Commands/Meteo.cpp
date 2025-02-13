#include "../Command.hpp"
#include <cstdlib>
#include <fstream>

Meteo::Meteo(Server* srv) : Command(srv) 
{

}

Meteo::~Meteo() 
{

}

size_t countChars(const std::string& str, char target, size_t startPos) {
    size_t count = 0;
    for (size_t i = startPos; i < str.size(); ++i) {
        if (str[i] == target) {
            return count;
        }
        count++;
    }
    return count;
}

void    Meteo::execute(Client* client, std::vector<std::string> args)
{
    if (*_srv->get_botStatus() == false)
    {
        client->reply(ERR_NOBOTINCHAN(client->get_nickname()));
        return;
    }
    if (args.empty() || args[0].empty()) 
    {
        client->reply(ERR_NOCITYGIVEN(client->get_nickname()));
        return;
    }
    std::string command = "./script.sh " + args[0];
    if (system(command.c_str()) != 0)
    {
        std::cerr << "Error while executing the meteo script." << std::endl;
        return;
    }
    usleep(100);
    std::ifstream file("weather.json");
    if (!file.is_open())
    {
		std::cerr << "file open error" << std::endl;
        return;
    }

    std::string buffer;
    std::string line;

    while(std::getline(file, buffer))
        buffer += line;
    file.close();
    size_t pos = buffer.find("cod\":") + 5;
    std::string cod = buffer.substr(pos, 3);

    if (strcmp(cod.c_str(), "\"40") == 0)
    {
        std::cerr << "invalid city name" << std::endl;
        system("rm -rm weather.json");
        return ;
    }
    
    pos = buffer.find("main\":\"") + 7;
    std::string weather = buffer.substr(pos, countChars(buffer, '\"', pos));
    pos = buffer.find("temp\":") + 6;
    std::string temp = buffer.substr(pos, countChars(buffer, ',', pos));
    pos = buffer.find("speed\":") + 7;
    std::string wind = buffer.substr(pos, countChars(buffer, ',', pos));
    pos = buffer.find("country\":\"") + 10;
    std::string country = buffer.substr(pos, countChars(buffer, '\"', pos));
    pos = buffer.find("name\":\"") + 7;
    std::string city = buffer.substr(pos, countChars(buffer, '\"', pos));
    std::string output = "Here's the actual weather in " + city + "(" + country + ")\n"
                            + "The weather is " + weather + ", and the temperature is " + temp + " degrees celsius.\n"
                            + "The wind is blowing at a speed of " + wind + " meter/sec.\n";
    client->write(output);
    system("rm -rm weather.json");
}
