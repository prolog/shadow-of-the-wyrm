#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "KeyboardCommandMap.hpp"

using KeyboardCommandMapSerializationMap = std::map<ClassIdentifier, KeyboardCommandMapPtr>;

class KeyboardCommandMapFactory
{
  public:
    KeyboardCommandMapFactory(const KeyboardCommandMapFactory&) = delete;
    bool operator=(const KeyboardCommandMapFactory&) = delete;

    static KeyboardCommandMapPtr create_keyboard_command_map(const ClassIdentifier ci);

  protected:
    static void initialize_command_map_map();
    static KeyboardCommandMapSerializationMap kb_map;
};

