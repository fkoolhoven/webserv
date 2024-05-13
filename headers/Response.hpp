/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Response.hpp                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fkoolhov <fkoolhov@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/04/23 17:04:25 by fkoolhov      #+#    #+#                 */
/*   Updated: 2024/05/10 22:11:21 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "webserv.hpp"
# include "Request.hpp"
# include "Server.hpp"
# include "ErrorHandler.hpp"
# include "RequestHandler.hpp"

class Response
{
	private:
		Server&								_server;
		short								_statusCode;
		std::string							_reasonPhrase;
		std::string							_statusLine; // http version, status code, reason phrase
		std::map<std::string, std::string>	_responseHeaders;
		std::string							_body;
		std::string							_responseMessage; // status line , headers + CRLF + body + 2 * CRLF

	public:
		Response(RequestHandler& requestHandler);
		Response(ErrorHandler& errorHandler);
		~Response();

		void	setStatusCode(short statusCode);
		void	setReasonPhrase(short statusCode);
		void	setStatusLine(std::string statusLine);
		void	addResponseHeader(std::string name, std::string value);
		void	setBody(std::string body);
		void	setResponseMessage(std::string responseMessage);
		
		Server&									getServer() const;
		short									getStatusCode() const;
		std::string								getStatusLine() const;
		std::map<std::string, std::string>		getResponseHeaders() const;
		std::string								getBody() const;
		std::string								getResponseMessage() const;

		std::string							constructStatusLine();
		std::map<std::string, std::string>	constructHeaders();
		std::string							constructResponseMessage();
		void								addHeaders();
};

std::ostream&	operator<<(std::ostream& out_stream, const Response& response);
std::string 	getContentType(std::string filename);

#endif