#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Display.hpp"

typedef std::map<ClassIdentifier, DisplayPtr> DisplaySerializationMap;

class DisplayFactory
{
  public:
    static DisplayPtr create_display(const ClassIdentifier ci);

  private:
    static void initialize_display_map();

    static DisplaySerializationMap display_map;
};

