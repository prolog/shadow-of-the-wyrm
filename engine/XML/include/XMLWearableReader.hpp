#pragma once
#include "Wearable.hpp"
#include "XMLItemReader.hpp"

// A class for reading attributes and elements common to all Wearable
// items.
class XMLWearableReader : public XMLItemReader
{
  public:
    XMLWearableReader();
    ~XMLWearableReader();

  protected:
    void parse(WearablePtr wearable, const XMLNode& wearable_node);
};
