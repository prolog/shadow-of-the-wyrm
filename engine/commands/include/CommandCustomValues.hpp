#pragma once
#include <string>

class CommandCustomValues
{
  public:
    static const std::string COMMAND_CUSTOM_VALUES_ACTION_COST_VALUE;
    static const std::string COMMAND_CUSTOM_VALUES_SELECTED_SPELL_ID;
    static const std::string COMMAND_CUSTOM_VALUES_DIRECTION;

  protected:
    CommandCustomValues();
    ~CommandCustomValues();
};

