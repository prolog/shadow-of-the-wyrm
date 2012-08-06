#pragma once
#include "CommandFactory.hpp"

class TileSelectionCommandFactory : public CommandFactory
{
  public:
    TileSelectionCommandFactory();
    virtual ~TileSelectionCommandFactory();

  virtual CommandPtr create(const int key, const std::string& command_name);
  virtual CommandFactoryType get_factory_type() const;
};
