#pragma once
#include "CodexDescriber.hpp"
#include "Spellbook.hpp"

class SpellbookCodexDescriber : public CodexDescriber
{
  public: 
    SpellbookCodexDescriber(SpellbookPtr spellbook);
    virtual ~SpellbookCodexDescriber() = default;

    std::string describe_for_synopsis_line() const override;

  protected:
    SpellbookPtr spellbook;
};

