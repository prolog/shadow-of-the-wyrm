#pragma once
#include <string>

class Environment
{
  public:
    static std::string get_user_name();
    static std::string get_user_home_directory();
};

