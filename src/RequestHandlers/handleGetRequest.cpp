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

#include "RequestHandler.hpp"

std::string RequestHandler::constructBodyFromDirectory()
{
    std::string body;

    if (!_location.getDirectoryListing())
    {
        std::string defaultPage = _location.getDefaultPage();
        if (defaultPage.empty())
            throw StatusCodeException("Requested path is a directory", FORBIDDEN);
        addHeader("Content-Type", "text/html");
        return constructBodyFromFile(defaultPage);
    }
    DIR* dir_stream = opendir(_absPath.c_str());
    if (!dir_stream)
        throw StatusCodeException("Couldn't open directory", FORBIDDEN);
    struct dirent *dirent;
    body = "<!DOCTYPE html>\r\n<html lang=\"en\">\r\n<head>\r\n\t<meta charset=\"UTF-8\">\r\n\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\r\n\t<title>Directory Listing</title>\r\n\t<link rel=\"stylesheet\" href=\"/styles/styles.css\">\r\n</head>\r\n<body>\r\n\t<h1>Directory Listing</h1>\r\n\t<p>The page you requested is a directory with the following content:</p>\r\n\t<ul>\r\n";
    while ((dirent = readdir(dir_stream)))
    {
        if (dirent->d_name[0] != '.')
        {
            body += "\t\t<li><a href=\"" + _request.getPath();
            if (_request.getPath().back() != '/') 
                body += "/";
            body += dirent->d_name;
            body += "\">";
            body += dirent->d_name;
            body += "</a></li>\r\n";
        }
    }
    body += "\t</ul>\r\n</body>\r\n</html>";
    closedir(dir_stream);
    addHeader("Content-Type", "text/html");
    return body;
}

std::string RequestHandler::constructBody()
{
    std::string body;
    
    if (std::filesystem::is_directory(_absPath))
        return constructBodyFromDirectory();
    body = constructBodyFromFile(_absPath);
    addHeader("Content-Type", getContentType(_extension));
    return body;
}

void RequestHandler::handleGetRequest()
{
    std::string extension;
    std::string path;

    path = _request.getPath();

    if (path.find_last_of('.') != std::string::npos)
        extension = path.substr(path.find_last_of('.'));
    if (extension.size() != 0 && extension == _location.getCgiExtension())
    {
        _CGI = true;
        return ;
    }
    setBody(constructBody());
}