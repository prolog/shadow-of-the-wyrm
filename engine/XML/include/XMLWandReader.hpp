#pragma once
#include "XMLDataStructures.hpp"
#include "XMLItemReader.hpp"
#include "Wand.hpp"

class XMLWandReader : public XMLItemReader
{
  public:
    XMLWandReader();
    ~XMLWandReader();
    
    void parse(WandPtr wand, GenerationValues& igv, const XMLNode& potion_node);
};

