#include "Server.hpp"
#include <csignal>

static void sig_handler(int signum);
static sig_atomic_t stopRequested = true;

int main(int argc, char **argv)
{
    if (argc != 3)
        throw std::runtime_error("Wrong number of arguments, IP then Port needed!");
    const int   port = atoi(argv[1]);
    if (port < 1024 || port > 65535)
        throw std::runtime_error("Wrong IP format!");
    Server  server(argv[1], argv[2]);
    server.set_stop(&stopRequested);
    std::signal(SIGINT, &sig_handler);
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