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

#ifndef SERVER_HPP
# define SERVER_HPP

# define BACKLOG 5

# include "webserv.hpp"
# include "ASocket.hpp"
# include "Location.hpp"
# include "Client.hpp"

# include <vector>
# include <map>
# include <memory> // for unique_ptr
# include <sys/socket.h> // for socket(), bind(), listen()
# include <cstring> // for memset
# include <netdb.h> // getaddrinfo()
# include <string> // for to_string
# include <unistd.h> // for close
# include <arpa/inet.h> // * for inet_ntop() only to print info - might remove?
# include <sys/epoll.h> // for EPOLLIN

class Server : public ASocket
{
	private:
		int										_port;
		std::string								_host;
		std::vector<std::string>				_serverNames;
		std::string								_rootFolder;
		std::map<short, std::string>			_customErrorPages;
		unsigned long long						_clientMaxBodySize;
		std::vector<std::unique_ptr<Location>>	_locations;
		const std::unique_ptr<Location>			_defaultLocation;
		struct addrinfo*						_serverInfo{};
		std::map<int, std::unique_ptr<Client>>	_connectedClients;

	public:
		Server(int port,
				std::string host,
				std::vector<std::string> serverNames,
				std::string rootFolder,
				std::map<short, std::string> customErrorPages,
				unsigned long long clientMaxBodySize,
				std::vector<std::unique_ptr<Location>> locations,
				std::unique_ptr<Location> defaultLocation);
		~Server();

		void	setPort(int port);
		void	setHost(std::string host);
		void	addServerName(std::string serverName);
		void	setRootFolder(std::string rootFolder);
		void	addCustomErrorPage(short errorCode, std::string errorPage);
		void	setClientMaxBodySize(unsigned long long clientMaxBodySize);
		void	addLocation(std::unique_ptr<Location> location);

		int												getPort() const;
		std::string										getHost() const;
		std::vector<std::string>						getServerNames() const;
		std::string										getRootFolder() const;
		std::map<short, std::string>					getCustomErrorPages() const;
		unsigned long long								getClientMaxBodySize() const;
		const std::vector<std::unique_ptr<Location>>&	getLocations() const;
		const Location&									getDefaultLocation() const;
		struct addrinfo* 								getServerInfo() const;
		const std::map<int, std::unique_ptr<Client>>&	getConnectedClients() const;

		void	createNewClientConnection();
		void	removeClientConnection(Client* client);

		class ServerConfigError : public std::exception 
		{
			public:
				explicit ServerConfigError(const std::string& message) 
					: message_(RED BOLD "Server config error: " RESET + message) {}

				virtual const char* what() const noexcept override 
				{
					return message_.c_str();
				}

			private:
				std::string message_;
		};
};

std::ostream& operator<<(std::ostream& out_stream, const Server& server);

#endif
