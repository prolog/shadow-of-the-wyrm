#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "KeyboardCommandMap.hpp"

typedef std::map<ClassIdentifier, KeyboardCommandMapPtr> KeyboardCommandMapSerializationMap;

class KeyboardCommandMapFactory
{
  public:
    static KeyboardCommandMapPtr create_keyboard_command_map(const ClassIdentifier ci);

  protected:
    static void initialize_command_map_map();
    static KeyboardCommandMapSerializationMap kb_map;
};

