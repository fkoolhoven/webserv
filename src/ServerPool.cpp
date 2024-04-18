/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerPool.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:03:06 by felicia           #+#    #+#             */
/*   Updated: 2024/04/18 19:24:13 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerPool.hpp"

ServerPool::ServerPool()
{
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

std::ostream& operator<<(std::ostream& out_stream, const ServerPool& server_pool)
{
	const std::vector<std::unique_ptr<Server>>& servers = server_pool.getServers();
	for (std::vector<std::unique_ptr<Server>>::const_iterator it = servers.begin(); it != servers.end(); ++it)
	{
		const std::unique_ptr<Server>& server = *it;
		out_stream << *server << std::endl;
	}
	return out_stream;
}