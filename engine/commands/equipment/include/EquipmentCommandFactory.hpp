#pragma once
#include "CommandFactory.hpp"

class EquipmentCommandFactory : public CommandFactory
{
  public:
    EquipmentCommandFactory();
    virtual ~EquipmentCommandFactory();

    virtual CommandPtr create(const int key, const std::string& command_name);
    virtual CommandFactoryType get_factory_type() const;

    virtual CommandFactory* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};
