#pragma once
#include "CommandFactory.hpp"

class HelpCommandFactory : public CommandFactory
{
  public:
    HelpCommandFactory();
    virtual ~HelpCommandFactory();

    virtual CommandPtr create(const int key, const std::string& command_name) override;
    virtual CommandFactoryType get_factory_type() const override;

    virtual CommandFactory* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
