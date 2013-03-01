#pragma once
#include "XMLDataStructures.hpp"
#include "XMLItemReader.hpp"
#include "Readable.hpp"

class XMLReadableReader : public XMLItemReader
{
  public:
    XMLReadableReader();
    ~XMLReadableReader();

    void parse(ReadablePtr readable, GenerationValues& gv, const XMLNode& readable_node);
};
