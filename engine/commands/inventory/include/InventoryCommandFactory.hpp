#pragma once
#include "CommandFactory.hpp"

class InventoryCommandFactory : public CommandFactory
{
  public:
    InventoryCommandFactory();
    virtual ~InventoryCommandFactory();

    virtual CommandPtr create(const std::string& command);
};
