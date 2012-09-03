#pragma once
#include "XMLDataStructures.hpp"
#include "XMLItemReader.hpp"
#include "Potion.hpp"

class XMLPotionReader : public XMLItemReader
{
  public:
    XMLPotionReader();
    ~XMLPotionReader();

    void parse(PotionPtr potion, const XMLNode& potion_node);
};

