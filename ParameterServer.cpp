#include "ParameterServer.h"

ParameterServer::ParameterServer()
{}

bool ParameterServer::get_bool(const std::string &uri)
{
    return false;
}

int ParameterServer::get_int(const std::string &uri)
{
    return 0;
}

float ParameterServer::get_float(const std::string &uri)
{
    return 0.0f;
}

std::string ParameterServer::get_string(const std::string &uri)
{
    return std::string();
}

error_code ParameterServer::set_bool(const std::string &uri, bool value)
{
    return 0;
}

error_code ParameterServer::set_int(const std::string &uri, int value)
{
    return 0;
}

error_code ParameterServer::set_float(const std::string &uri, float value)
{
    return 0;
}

error_code ParameterServer::set_string(const std::string &uri, const std::string &value)
{
    return 0;
}
