#pragma once
#include "KeyboardCommandMap.hpp"

class EquipmentKeyboardCommandMap : public KeyboardCommandMap
{
  public:
    EquipmentKeyboardCommandMap();
    virtual ~EquipmentKeyboardCommandMap();

    // Fail silently.
    virtual void command_not_found(const std::string& keyboard_input) override;
  
    std::string get_settings_prefix() const override;

    // serialize/deserialize taken care of by KeyboardCommandMap

    virtual KeyboardCommandMap* clone() override;

  protected:
    friend class SL_Engine_Commands_Equipment_EquipmentKeyboardCommandMapFixture;

    // The equipment keys mean different things than the parent class's
    // map!
    virtual void initialize_command_mapping(const Settings& settings) override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
