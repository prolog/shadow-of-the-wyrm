#pragma once
#include "Class.hpp"

class ClassManager
{
  public:
    ClassManager();

    ClassPtr get_class(const std::string& class_id);
};
