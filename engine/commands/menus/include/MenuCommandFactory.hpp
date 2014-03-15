#pragma once
#include "CommandFactory.hpp"

class MenuCommandFactory : public CommandFactory
{
  public:
    MenuCommandFactory();
    virtual ~MenuCommandFactory();

    virtual CommandPtr create(const int key, const std::string& command_name) override;
    virtual CommandFactoryType get_factory_type() const override;

    virtual CommandFactory* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
