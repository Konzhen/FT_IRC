#include <sys/socket.h>
#include <vector>
#include <csignal>
#include <signal.h>
#include <iostream>
#include <cstdlib>
#include "Bot.hpp"

static void sighandler(int signum);
static void    check_args(int argc, char **argv);

static sig_atomic_t stopRequested = true;
static int          pid_srv;

int main(int argc, char** argv)
{
    try
    {
        check_args(argc, argv);
        Bot bot(atoi(argv[1]), argv[2], argv[3], atoi(argv[4]));
        pid_srv = atoi(argv[4]);
        signal(SIGINT, sighandler);

        while (true)
        {
            if (stopRequested == false)
                exit(0);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

static void    check_args(int argc, char **argv)
{
    if (argc != 5)
        throw std::runtime_error("Wrong usage of the program\nUse it that way : ./robometeo <host ip> <port> <password> <host program id>");
    std::string host = argv[1];
    std::string port = argv[2];
    std::string password = argv[3];
    std::string pid = argv[4];
    if (host.empty())
        throw std::runtime_error("Invalid host ip");
    if (port.empty() || port.length() > 5 || atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65535)
        throw std::runtime_error("Invalid port");
    if (password.empty())
        throw std::runtime_error("Invalid password.");
    if(pid.empty() || pid.length() > 9 || atoi(pid.c_str()) <= 0 || atol(pid.c_str()) >= 2147483647)
        throw std::runtime_error("Invalid pid");
}

static void	sighandler(int signum)
{
    (void)signum;
	std::cout << "SIGINT intercepted, exiting bot protocol" << std::endl;
    stopRequested = false;
    kill(pid_srv, SIGUSR2);
	return ;
}