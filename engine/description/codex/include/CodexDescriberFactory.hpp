#pragma once
#include "CodexDescriber.hpp"
#include "Item.hpp"

class CodexDescriberFactory
{
  public:
    CodexDescriberPtr create_codex_describer(const ItemPtr item);
};

