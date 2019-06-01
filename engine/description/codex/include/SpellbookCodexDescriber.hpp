#pragma once
#include "CodexDescriber.hpp"
#include "Spellbook.hpp"

class SpellbookCodexDescriber : public CodexDescriber
{
  public: 
    SpellbookCodexDescriber(ItemPtr item);

    std::string describe_for_synopsis_line() const override;
};

