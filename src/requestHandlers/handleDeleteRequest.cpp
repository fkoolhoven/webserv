#include "RequestHandler.hpp"
#include <filesystem>


void RequestHandler::handleDeleteRequest()
{
    std::filesystem::path filePath(getAbsolutePath(_request.getPath()));

    if (std::filesystem::exists(filePath))
    {
        if (std::filesystem::remove_all(filePath))
            setStatusCode(204);
        else
            throw (500);
    }
    else
        throw (404);
}
