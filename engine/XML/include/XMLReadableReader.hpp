#pragma once
#include "XMLDataStructures.hpp"
#include "XMLItemReader.hpp"
#include "Readable.hpp"

class XMLReadableReader : public XMLItemReader
{
  public:
    XMLReadableReader();
    ~XMLReadableReader();

    void parse(ReadablePtr readable, const XMLNode& readable_node);
};
