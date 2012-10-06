#pragma once
#include "ClassIdentifiers.hpp"
#include "Display.hpp"

class DisplayFactory
{
  public:
    static DisplayPtr create_display(const ClassIdentifier ci);
};

