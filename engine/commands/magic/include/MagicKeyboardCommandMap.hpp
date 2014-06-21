#pragma once
#include "KeyboardCommandMap.hpp"

class MagicKeyboardCommandMap : public KeyboardCommandMap
{
  public:
    MagicKeyboardCommandMap();
    virtual ~MagicKeyboardCommandMap();

    // Fail silently.
    virtual void command_not_found(const std::string& keyboard_input) override;
  
    std::string get_settings_prefix() const override;

    // serialize/deserialize taken care of by KeyboardCommandMap

    virtual KeyboardCommandMap* clone() override;

  protected:
    virtual void initialize_command_mapping(const Settings& settings) override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
