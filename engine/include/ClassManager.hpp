#pragma once
#include "Creature.hpp"

class ClassManager
{
  public:
    ClassManager();

    Class* get_class(const std::string& class_id);
    std::string get_title(CreaturePtr creature);
};
