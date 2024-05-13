/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerPool.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mverbrug <mverbrug@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:03:06 by felicia           #+#    #+#             */
/*   Updated: 2024/05/13 12:41:25 by mverbrug         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerPool.hpp"

ServerPool::ServerPool()
{
	_epoll = std::make_unique<Epoll>();
	std::cout << "ServerPool constructor called" << std::endl;
}

ServerPool::~ServerPool()
{
	std::cout << "ServerPool destructor called" << std::endl;
}

void ServerPool::addServer(std::unique_ptr<Server> server)
{
	this->_servers.push_back(std::move(server));
}

const std::vector<std::unique_ptr<Server>>& ServerPool::getServers() const
{
	return this->_servers;
}

std::vector<std::unique_ptr<Server>>& ServerPool::getServers()
{
	return this->_servers;
}

Epoll& ServerPool::getEpollInstance() const
{
	return *(this->_epoll);
}

std::ostream& operator<<(std::ostream& out_stream, const ServerPool& server_pool)
{
	std::cout << std::endl;
	const std::vector<std::unique_ptr<Server>>& servers = server_pool.getServers();
	for (std::vector<std::unique_ptr<Server>>::const_iterator it = servers.begin(); it != servers.end(); ++it)
	{
		const std::unique_ptr<Server>& server = *it;
		out_stream << *server << std::endl;
	}
	return out_stream;
}