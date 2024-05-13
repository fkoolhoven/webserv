/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   requestHandlerUtils.cpp                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/10 20:58:05 by fhuisman      #+#    #+#                 */
/*   Updated: 2024/05/10 21:14:55 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <fstream>
#include <map>

std::string getReasonPhrase(short statusCode)
{
    std::map<short, std::string> reasonPhrases = {{100, "Continue"}, {101, "Switching Protocols"}, {200, "OK"}, {201, "Created"}, {202, "Accepted"}, {203, "Non-Authoritative Information"}, {204, "No Content"}, {205, "Reset Content"}, {206, "Partial Content"}, {300, "Multiple Choices"}, {301, "Moved Permanently"}, {302, "Found"}, {303, "See Other"}, {304, "Not Modified"}, {305, "Use Proxy"}, {307, "Temporary Redirect"}, {400, "Bad Request"}, {401, "Unauthorized"}, {402, "Payment Required"}, {403, "Forbidden"}, {404, "Not Found"}, {405, "Method Not Allowed"}, {406, "Not Acceptable"}, {407, "Proxy Authentication Required"}, {408, "Request Time-out"}, {409, "Conflict"}, {410, "Gone"}, {411, "Length Required"}, {412, "Precondition Failed"}, {413, "Request Entity Too Large"}, {414, "Request-URI Too Large"}, {415, "Unsupported Media Type"}, {416, "Requested range not satisfiable"}, {417, "Expectation Failed"}, {500, "Internal Server Error"}, {501, "Not Implemented"}, {502, "Bad Gateway"}, {503, "Service Unavailable"}, {504, "Gateway Time-out"}, {505, "HTTP Version not supported"}};
    auto it = reasonPhrases.find(statusCode);
    if (it == reasonPhrases.end())
        ;//ik denk dat dit nooit voorkomt, want dan hebben we zelf een statuscode gethrowt die niet bestaat. toch implementeren?
    return (*it).second;
}

std::string constructBodyFromFile(std::string pathToFile)
{
    std::string body;
    std::string line;
    std::ifstream file;

    file.open(pathToFile);
    if (!file.is_open())
        throw (404);
    if (std::getline(file, line))
        body += line;
    while (std::getline(file, line))
    {
        body += "\r\n" + line;
    }
    file.close();
    return (body);
}

std::string getContentType(std::string filename)
{
    std::map<std::string, std::string> contentTypes = {{".html", "text/html"}, {".css", "text/css"}, {".js", "application/javascript"}, {".json", "application/json"}, {".jpg", "image/jpeg"}, {".jpeg", "image/jpeg"}, {".png", "image/png"}, {".gif", "image/gif"}, {".pdf", "application/pdf"}, {".txt", "text/plain"}, {".xml", "application/xml"}};

    filename = filename.substr(filename.find_last_of('.'));
    auto it = contentTypes.find(filename);
    if (it == contentTypes.end())
        return ("application/octet-stream");
    return ((*it).second);
}