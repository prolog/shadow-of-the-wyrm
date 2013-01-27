#pragma once
#include "XMLDataStructures.hpp"
#include "XMLItemReader.hpp"
#include "Tool.hpp"

class XMLToolReader : public XMLItemReader
{
  public:
    XMLToolReader();
    ~XMLToolReader();

    void parse(ToolPtr tool, const XMLNode& tool_node);
};

