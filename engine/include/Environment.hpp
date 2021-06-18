#pragma once
#include <string>
#include "Settings.hpp"

class Environment
{
  public:
    static std::string get_log_directory(const Settings* settings);

    static bool create_userdata_directory(const Settings* settings);
    static std::string get_userdata_directory(const Settings* settings); // saves and char dumps

    static std::string get_user_name();
    static std::string get_user_home_directory();
};

