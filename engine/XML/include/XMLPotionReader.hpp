#pragma once
#include "XMLDataStructures.hpp"
#include "XMLConsumableReader.hpp"
#include "Potion.hpp"

class XMLPotionReader : public XMLConsumableReader
{
  public:
    XMLPotionReader();
    ~XMLPotionReader();

    void parse(PotionPtr potion, GenerationValues& igv, const XMLNode& potion_node);
};

