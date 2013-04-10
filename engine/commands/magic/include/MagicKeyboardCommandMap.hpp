#pragma once
#include "KeyboardCommandMap.hpp"

class MagicKeyboardCommandMap : public KeyboardCommandMap
{
  public:
    MagicKeyboardCommandMap();
    virtual ~MagicKeyboardCommandMap();

    // Fail silently.
    virtual void command_not_found(const std::string& keyboard_input);
  
    // serialize/deserialize taken care of by KeyboardCommandMap

    virtual KeyboardCommandMap* clone();

  protected:
    virtual void initialize_command_mapping();

  private:
    ClassIdentifier internal_class_identifier() const;
};
