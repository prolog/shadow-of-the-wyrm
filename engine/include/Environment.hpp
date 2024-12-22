#pragma once
#include <string>
#include "Settings.hpp"

class Environment
{
  public:
    static bool create_userdata_directory(const Settings* settings);
    static bool create_empty_user_settings_if_necessary(const Settings* settings);

    static std::string get_log_directory(const Settings* settings);
    static std::string get_userdata_directory(const Settings* settings); // saves and user-requested char dumps
    static std::string get_syschardump_directory(const Settings* settings); // system char dumps only
    static std::string get_scorefile_directory(const Settings* settings); // where should the high score file be written to/read from?

    static std::string get_user_name();
    static std::string get_user_home_directory();
};

