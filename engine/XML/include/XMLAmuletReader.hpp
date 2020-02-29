#pragma once
#include "XMLWearableReader.hpp"
#include "Amulet.hpp"

class XMLAmuletReader : public XMLWearableReader
{
  public:
    XMLAmuletReader();
    ~XMLAmuletReader();

    void parse(AmuletPtr amulet, GenerationValues& igv, const XMLNode& amulet_node);

  protected:
};
