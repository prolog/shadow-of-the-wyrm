#pragma once
#include <string>
#include "Resistances.hpp"

class ResistancesDisplayOptions
{
  public:
    ResistancesDisplayOptions(const bool new_use_braces, const bool new_use_abbreviations);

    bool get_use_braces() const;
    bool get_use_abbreviations() const;
  
  protected:
    bool use_braces;
    bool use_abbreviations;
};

// A class used for translating a Resistances object into a UI-friendly
// string
class ResistancesTranslator
{
  public:
    std::string create_description(const Resistances& res, const ResistancesDisplayOptions& rt);
};

