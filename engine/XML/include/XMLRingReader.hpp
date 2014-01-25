#pragma once
#include "XMLWearableReader.hpp"
#include "Ring.hpp"

class XMLRingReader : public XMLWearableReader
{
  public:
    XMLRingReader();
    ~XMLRingReader();
  
    void parse(RingPtr ring, GenerationValues& igv, const XMLNode& ring_node);

protected:
};

