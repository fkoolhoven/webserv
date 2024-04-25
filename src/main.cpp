/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:01:35 by mverbrug          #+#    #+#             */
/*   Updated: 2024/04/25 14:55:14 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"
#include "configuration.hpp"
#include "Request.hpp"
#include "Response.hpp"

int main(int argc, char** argv)
{
	std::string http_request = "GET /path HTTP/1.1\r\nheaderName: headerValue\r\n\t..continuation\r\n\t...CONTINUATION\r\nheaderName2: headerValue2\r\nheaderName: otherValue\r\nHost: localhost:8080\r\n\r\nThis is the body of the request\r\nThis is the body of the request\r\n\r\n";
	
	if (argc != 2)
	{
		// handle error
		return (EXIT_FAILURE);
	}
	
	std::unique_ptr<ServerPool> serverpool = configure_serverpool(argv[1]);
	std::cout << *serverpool << std::endl; // for debugging purposes
	try 
	{
		std::unique_ptr<Request> request = std::make_unique<Request>(http_request);
		std::unique_ptr<Response> response = std::make_unique<Response>(std::move(request));
		std::cout << *(response->getRequest()) << std::endl; // for for debugging purposes
		std::cout << *response << std::endl; // for for debugging purposes
		response->constructResponseMessage(); // function to fill in, should construct http response string
		std::string http_response = response->getResponseMessage();
		std::cout << "Response: " << http_response << std::endl; // for for debugging purposes
	}
	catch (char const *error)
	{
		std::cout << error << std::endl; //for debugging purposes
		//send error response
	}
	return (EXIT_SUCCESS);
}