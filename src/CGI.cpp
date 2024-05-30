/* ************************************************************************* */
/*      ##       ##      ## ##       ##      ## ##       ##      ##          */
/*       ##     ####    ##   ##     ####    ##   ##     ####    ##           */
/*        ##  ##   ##  ##     ##  ##   ##  ##     ##  ##   ##  ##            */
/*         ####     ####       ####     ####       ####     ####             */
/*          ##       ##         ##       ##         ##       ##              */
/*                                                                           */
/*           WONDERFUL            WEBSERV           WONDERTEAM               */
/*                                                                           */
/*      FELICIA KOOLHOVEN      FLEN HUISMAN       MARES VERBRUGGE            */
/*          fkoolhov             fhuisman             mverbrug               */
/*                                                                           */
/*          Codam Coding College        part of 42 network                   */
/*                            April - May 2024                               */
/* ************************************************************************* */

# include "CGI.hpp"

CGI::CGI(int pipe_fd, Client& client) : _client(client)
{
	_socketFD = pipe_fd;
	if (_client.getServer().getEpollReference().addFDToEpoll(this, EPOLLIN, _socketFD) < 0)
	{
		close(_socketFD); // close CGI socket
		throw std::runtime_error("Error adding fd to epoll");
	}
	std::cout << "CGI constructor called" << std::endl;
}

CGI::CGI(int pipe_fd, Client& client, char **envp, std::string script_string) : _client(client), _envp(envp), _script_string(script_string)
{
	_socketFD = pipe_fd;
	if (_client.getServer().getEpollReference().addFDToEpoll(this, EPOLLOUT, _socketFD) < 0)
	{
		close(_socketFD); // close CGI socket
		throw std::runtime_error("Error adding fd to epoll");
	}
	std::cout << "CGI constructor called" << std::endl;
}

CGI::~CGI()
{
	close(_socketFD); // close CGI socket
	std::cout << "CGI destructor called" << std::endl;
}

void CGI::run_script()
{
	dup2(_socketFD, STDOUT_FILENO); // add WRITE end to epoll! (MARES)

    const char* python_path = "/usr/bin/python3";
    const char* python_script = _script_string.c_str();
	char *const argv[] = { const_cast<char *>(python_path), const_cast<char *>(python_script), NULL };

    execve(python_path, argv, _envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void CGI::cgiReads()
{
	char response[BUFSIZ]{};
	ssize_t bytes_received{};

	bytes_received = read(_socketFD, response, BUFSIZ - 1);
	_client.setResponse(response);
	// std::cout << BOLD GREEN "Response in cgiReads = \n" << response << RESET; 
	_client.setReadyForFlag(WRITE);
}