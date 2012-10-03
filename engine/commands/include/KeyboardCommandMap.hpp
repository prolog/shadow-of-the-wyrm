#pragma once
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

class KeyboardCommandMap
{
  public:
    KeyboardCommandMap();
    virtual ~KeyboardCommandMap();

    virtual std::string get_command_type(const std::string& keyboard_input);

  protected:
    virtual void command_not_found(const std::string& keyboard_input);
    virtual void initialize_command_mapping();
    std::map<std::string, std::string> command_mapping;
};

typedef boost::shared_ptr<KeyboardCommandMap> KeyboardCommandMapPtr;
