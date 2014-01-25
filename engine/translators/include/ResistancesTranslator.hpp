#pragma once
#include <string>
#include "Resistances.hpp"

// A class used for translating a Resistances object into a UI-friendly
// string
class ResistancesTranslator
{
  public:
    std::string create_description(const Resistances& res);
};

