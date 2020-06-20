#pragma once
#include "Consumable.hpp"
#include "XMLItemReader.hpp"

class XMLConsumableReader : public XMLItemReader
{
  public:
    XMLConsumableReader();
    ~XMLConsumableReader();

    void parse(ConsumablePtr consumable, GenerationValues& gv, const XMLNode& consumable_node);
};
