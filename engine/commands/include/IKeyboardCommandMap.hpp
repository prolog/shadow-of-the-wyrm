#pragma once
#include <string>

// Keyboard command map interface
class IKeyboardCommandMap
{
  public:
    virtual std::string get_settings_prefix() const = 0;
};
