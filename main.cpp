#include "Server.hpp"
#include <csignal>

static void sig_handler(int signum);
static void sig_handler_bot(int signum);
static sig_atomic_t botStatus = false;
static sig_atomic_t stopRequested = true;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Wrong number of arguments, IP then Port needed!" << std::endl;
        return(1);
    }
    std::string port = argv[1];
    std::string pass = argv[2];
    if (pass.empty())
    {
        std::cerr << "Wrong arguments, password can't be empty!" << std::endl;
        return(1);
    }
    if (port.empty() || port.length() > 5 || atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65535)
    {
        std::cerr << "Wrong port format!" << std::endl;
        return(1);
    }
    Server  server(argv[1], argv[2]);
    server.set_stop(&stopRequested);
    server.set_bot(&botStatus);
    std::signal(SIGUSR1, &sig_handler_bot);
    std::signal(SIGINT, &sig_handler);
    std::signal(SIGUSR2, &sig_handler_bot);
    std::cout << getpid() << std::endl;
    try
    {
        server.start();
        return(0);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return(1);
    }
}

static void sig_handler(int signum)
{
    (void)signum;
    stopRequested = false;
}

static void sig_handler_bot(int signum)
{
    if(signum == SIGUSR1)
    {
        botStatus = true;
        std::cout << "Meteosaurus is now online! You can call it with the METEO <city> command" << std::endl;
    }
    if(signum == SIGUSR2)
    {
        botStatus = false;
        std::cout << "Meteosaurus has left the server, bye bye!" << std::endl;
    }
}