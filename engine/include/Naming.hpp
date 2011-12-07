#pragma once
#include <string>
#include "common.hpp"

class Naming
{
  public:
    static std::string clean_name(const std::string& name);

  protected:
    Naming();

    static uint MAXIMUM_NAME_SIZE;
};
