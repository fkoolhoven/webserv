/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   RequestHandler.cpp                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/09 16:22:31 by fhuisman      #+#    #+#                 */
/*   Updated: 2024/05/10 22:55:32 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "RequestHandler.hpp"

RequestHandler::RequestHandler(Request& request, Server& server) :  _request(request),
                                                                    _server(server),
                                                                    _location(matchLocation(_request.getPath())),
                                                                    _statusCode(200),
                                                                    _body("")
{
    std::cout << "RequestHandler constructor called" << std::endl;

    if (_location.getRedirectLink() != "")
    {
        redirect();
        return;
    }
    if(!methodIsAllowedOnLocation())
        throw (405);
    if (_request.getMethod() == GET)
        handleGetRequest();
    else if (_request.getMethod() == POST)
        handlePostRequest();
    else if(_request.getMethod() == DELETE)
        handleDeleteRequest();
}

RequestHandler::~RequestHandler()
{
    std::cout << "RequestHandler destructor called" << std::endl;
}


Request& RequestHandler::getRequest() const
{
    return (_request);
}

Server& RequestHandler::getServer() const
{
    return (_server);
}

Location& RequestHandler::getLocation() const
{
    return (_location);
}

short RequestHandler::getStatusCode() const
{
    return (_statusCode);
}

std::map<std::string, std::string> RequestHandler::getHeaders() const
{
    return (_headers);
}

std::string RequestHandler::getBody() const
{
    return (_body);
}

void RequestHandler::setStatusCode(short statusCode)
{
    _statusCode = statusCode;
}

void RequestHandler::addHeader(std::string name, std::string value)
{
    auto it = _headers.find(name);
    if (it != _headers.end())
        it->second += ", " + value;
    else
        _headers[name] = value;
}

void RequestHandler::setBody(std::string body)
{
    _body = body;
}

Location& RequestHandler::matchLocation(std::string path)
{
    if (path == "" || path == "/")
    {
        try
        {
            return (_server.getDefaultLocation());
        }
        catch(const std::exception& e)
        {
            throw (404);
        }
    }
    auto& locations = _server.getLocations();
    for (auto it = locations.begin(); it < locations.end(); it++)
    {
        Location& location = **it;
        if (location.getLocationName() == path)
            return (location);
    }
    return (matchLocation(path.substr(0, path.find_last_of('/'))));
}

bool RequestHandler::methodIsAllowedOnLocation()
{
    auto allowedMethods = _location.getAllowedMethods();
    return (allowedMethods[_request.getMethod()]);
}

void RequestHandler::redirect()
{
    setStatusCode(302);
    addHeader("Location", _location.getRedirectLink());
}

void RequestHandler::handlePostRequest()
{

}

void RequestHandler::handleDeleteRequest()
{

}