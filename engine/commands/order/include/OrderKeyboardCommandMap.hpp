#pragma once
#include "KeyboardCommandMap.hpp"

class OrderKeyboardCommandMap : public KeyboardCommandMap
{
  public:
    OrderKeyboardCommandMap(const bool new_followers_in_fov, const bool new_can_summon);
    virtual ~OrderKeyboardCommandMap();

    // Fail silently.
    virtual void command_not_found(const std::string& keyboard_input) override;

    std::string get_settings_prefix() const override;

    // serialize/deserialize taken care of by KeyboardCommandMap

    virtual KeyboardCommandMap* clone() override;

  protected:
    // The equipment keys mean different things than the parent class's
    // map!
    virtual void initialize_command_mapping(const Settings& settings) override;

    bool followers_in_fov;
    bool can_summon;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
