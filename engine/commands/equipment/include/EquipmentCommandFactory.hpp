#pragma once
#include "CommandFactory.hpp"

class EquipmentCommandFactory : public CommandFactory
{
  public:
    EquipmentCommandFactory();
    virtual ~EquipmentCommandFactory();

    virtual CommandPtr create(const std::string& command_name);
};
