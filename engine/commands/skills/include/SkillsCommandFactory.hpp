#pragma once
#include "CommandFactory.hpp"

enum class SkillSelectionType
{
  SKILL_SELECTION_TYPE_USE_SKILL = 0,
  SKILL_SELECTION_TYPE_IMPROVE_SKILL = 1
};

class SkillsCommandFactory : public CommandFactory
{
  public:
    SkillsCommandFactory();
    virtual ~SkillsCommandFactory();

    virtual CommandPtr create(const int key, const std::string& command_name) override;
    virtual CommandFactoryType get_factory_type() const override;

    virtual CommandFactory* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
