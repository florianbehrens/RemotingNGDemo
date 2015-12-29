#ifndef PARAMETER_SERVER_H
#define PARAMETER_SERVER_H

#include <cstdint>
#include <string>

typedef int error_code;

//@ remote
class ParameterServer
{
public:
    ParameterServer();

    bool get_bool(const std::string& uri);
    int get_int(const std::string& uri);
    float get_float(const std::string& uri);
    std::string get_string(const std::string& uri);

    error_code set_bool(const std::string& uri, bool value);
    error_code set_int(const std::string& uri, int value);
    error_code set_float(const std::string& uri, float value);
    error_code set_string(const std::string& uri, const std::string& value);
};

#endif // PARAMETER_SERVER_H
