#pragma once
#include "XMLReadableReader.hpp"
#include "Book.hpp"

class XMLBookReader : public XMLReadableReader
{
  public:
    XMLBookReader();
    ~XMLBookReader();

    void parse(BookPtr book, GenerationValues& igv, const XMLNode& book_node);
};

