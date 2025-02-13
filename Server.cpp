 #include "Server.hpp"

//--------------------------------------------------------------------------//
//                      - CONSTRUCTORS & DESTRUCTORS -                            //
//--------------------------------------------------------------------------//

Server::Server()
{

}

Server::Server(Server const &server)
{
    *this = server;
}

Server::Server(const std::string &port, const std::string &pass) : _host("127.0.0.1"), _port(port), _pass(pass)
{
    _dc = false;
    _running = 1;
    _size = 1;
    _sock = create_socket();
    _parser = new Parser(this);
}

Server::~Server() 
{
    delete _parser;
    for (size_t i = 0; i < _channels.size(); i++)
        delete _clients[i];
}


//--------------------------------------------------------------------------//
//                               - OPERATORS -                                    //
//--------------------------------------------------------------------------//

Server    &Server::operator=(Server const &server)
{
    (void)server;
    return (*this);
}


//--------------------------------------------------------------------------//
//                           - GETTERS & SETTERS -                                //
//--------------------------------------------------------------------------//
std::string     Server::get_password() const 
{
    return (_pass);
}

sig_atomic_t*     Server::get_botStatus()
{
    return (_botStatus);
}

Client*         Server::get_client(const std::string& nickname)
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        if (!nickname.compare(it_b->second->get_nickname()))
            return (it_b->second);
        it_b++;
    }
    return (NULL);
}

Channel*        Server::get_channel(const std::string& name)
{
    channel_iterator it_b = _channels.begin();
    channel_iterator it_e = _channels.end();

    while (it_b != it_e)
    {
        if (!name.compare((*it_b)->get_name()))
            return (*it_b);
        it_b++;
    }
    return (NULL);
}

void            Server::set_stop(sig_atomic_t *stop)
{
    _stopRequest = stop;
}

void            Server::set_bot(sig_atomic_t *bot)
{
    _botStatus = bot;
}
//--------------------------------------------------------------------------//
//                           - MEMBER FUNCTIONS -                           //
//--------------------------------------------------------------------------//

void            Server::start()
{
    short rv = 0;
    pollfd srv = {_sock, POLLIN, rv};
    _pfds[0] = srv;
    int i = 0;

    log("Server is listening...");
jump:
    while (_running)
    {
        if (poll(_pfds, _size, -1) < 0)
        {
            if (*_stopRequest == false)
            {
                std::cout << "\nSIGINT received, ending server protocol." << std::endl;
                say_goodbye();
                exit(0);
            }
            if (*_botStatus == true)
                goto jump;
            if (*_botStatus == false)
                goto jump;
            throw std::runtime_error("Error while polling from fd!");
        }
        for (i = 0; i != _size; i++)
        {
            if (i >= _size)
                break;
            if (_pfds[i].revents == 0)
                continue;
            if ((_pfds[i].revents & POLLHUP) == POLLHUP)
                break;
            if ((_pfds[i].revents & POLLIN) == POLLIN)
            {
                if (_pfds[i].fd == _sock)
                {
                    this->on_client_connect();
                    break;
                }
                this->on_client_message(_pfds[i].fd);
            }
        }
    }
}

void            Server::on_client_connect()
{
    int         fd;
    sockaddr_in addr = {};
    socklen_t   size = sizeof(addr);
    short       rv = 0;

    fd = accept(_sock, (sockaddr *) &addr, &size);
    if (fd < 0)
        throw std::runtime_error("Error while accepting a new client!"); 
    struct pollfd pfd = {fd, POLLIN, rv};
    _pfds[_size] = pfd;
    _size++;

    char hostname[NI_MAXHOST]; // defini a 1000 par sys/
    int res = getnameinfo((struct sockaddr *) &addr, sizeof(addr), hostname, NI_MAXHOST, NULL, 0, NI_NUMERICSERV);
    if (res != 0)
        throw std::runtime_error("Error while getting a hostname on a new client!");

    Client* client = new Client(fd, ntohs(addr.sin_port), hostname);
    _clients.insert(std::make_pair(fd, client));

    char message[1000];
    sprintf(message, "%s:%d has connected.", client->get_hostname().c_str(), client->get_port());
    log(message);
}

void            Server::on_client_disconnect(int fd)
{
    try
    {
        Client* client = _clients.at(fd);
        client->leave();
        char message[1000];
		sprintf(message, "%s:%d has disconnected!", client->get_hostname().c_str(), client->get_port());
		log(message);
        _clients.erase(fd);
        int i = 1;
        
        while (i != _size)
        {
            if (_pfds[i].fd == fd)
            {
                close(fd);
                while(i != _size)
                {
                    _pfds[i] = _pfds[i+1];
                    i++;
                }
                break;
            }
            i++;
        }
        delete client;
        _size--;
        return ;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error while disconnecting! " << e.what() << std::endl;
    }
}

void            Server::on_client_message(int fd)
{
    try
    {
        Client*     client = _clients.at(fd);
        std::string message = this->read_message(fd);
        _parser->invoke(client, message);
    }
    catch (const std::exception& e) 
    {
        if(!_dc)
            std::cout << "Error while handling the client message! :" << e.what() << std::endl;
        _dc = false;
    }
}

void            Server::say_goodbye()
{
    client_iterator it_b = _clients.begin();
    client_iterator it_e = _clients.end();

    while (it_b != it_e)
    {
        it_b->second->goodbye();
        close(it_b->second->get_fd());
        delete it_b->second;
        it_b++;
    }
    _clients.clear();

    channel_iterator ch_b = _channels.begin();
    channel_iterator ch_e = _channels.end();

    while (ch_b != ch_e)
    {
        delete *ch_b;
        ch_b++;
    }
    _channels.~vector();

    for (int i = 1; i != _size; i++)
        close (_pfds[i].fd);
    shutdown(_sock, SHUT_RDWR);
    close(_sock);
    delete(_parser);
}

std::string     Server::read_message(int fd)
{
    std::string message;
    char        buffer[100];
    ssize_t     rbytes;
    // if (recv(fd, buffer, sizeof(buffer), 0) == 0)
    //     return(buffer);
    bzero(buffer, 100); // 100 rapide et evite les problemes de desynchronisation, a modifier au besoin
    while (!strstr(buffer, "\n"))
    {
        bzero(buffer, 100);
        rbytes = recv(fd, buffer, 100, 0);
        if ((rbytes <= 0) and (errno != EWOULDBLOCK))
        {
            on_client_disconnect(fd);
            _dc = true;
            throw std::runtime_error("");
        }
        message.append(buffer);
    }
    return (message);
}

Channel*        Server::create_channel(const std::string& name, const std::string& key, Client* client)
{
    Channel *channel = new Channel(name, key, client);
    _channels.push_back(channel);
    return (channel);
}

int             Server::create_socket()
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
        throw std::runtime_error("Error while opening a socket!");
    int optval = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)))
        throw std::runtime_error("Error while setting socket options!");
    if (fcntl(sock_fd, F_SETFL, O_NONBLOCK))
        throw std::runtime_error("Error while setting socket to NON-BLOCKING!");
    
    struct sockaddr_in  serv_addr = {};
    bzero((char*) &serv_addr, sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(_port.c_str()));

    if (bind(sock_fd, (sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        throw std::runtime_error("Error while binding a socket!");
    if (listen(sock_fd, MAX_CONNECTIONS) < 0)
        throw std::runtime_error("Error while listening on a socket!");
    return (sock_fd);
}