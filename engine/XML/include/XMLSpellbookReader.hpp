#pragma once
#include "XMLReadableReader.hpp"
#include "Spellbook.hpp"

class XMLSpellbookReader : public XMLReadableReader
{
  public:
    XMLSpellbookReader();
    ~XMLSpellbookReader();

    void parse(SpellbookPtr book, GenerationValues& igv, const XMLNode& book_node);
};

