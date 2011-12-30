#pragma once
#include <string>
#include <map>

class KeyboardCommandMap
{
  public:
    static std::string get_command_type(const std::string& keyboard_input);

  protected:
    KeyboardCommandMap();
    ~KeyboardCommandMap();

    static void initialize_command_mapping();

    static std::map<std::string, std::string> command_mapping;
};
