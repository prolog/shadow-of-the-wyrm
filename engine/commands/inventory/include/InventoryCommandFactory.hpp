#pragma once
#include "CommandFactory.hpp"

class InventoryCommandFactory : public CommandFactory
{
  public:
    InventoryCommandFactory();
    virtual ~InventoryCommandFactory();

    virtual CommandPtr create(const int key, const std::string& command);
    virtual CommandFactoryType get_factory_type() const;
};
