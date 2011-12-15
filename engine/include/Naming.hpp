#pragma once
#include <string>
#include "common.hpp"

class Naming
{
  public:
    static std::string clean_name(const std::string& name);
    static uint get_max_name_size();
  protected:
    Naming();

    static uint MAXIMUM_NAME_SIZE;
};
