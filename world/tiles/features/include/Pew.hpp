#pragma once
#include "Feature.hpp"

// This is a "north-south" pew: the symbol is '-'.
// "east-west" pews are defined in EastWestPew.hpp.
class Pew : public Feature
{
  public:
    Pew();

    virtual bool handle();
    virtual bool kick();

    virtual uchar get_symbol() const;
    virtual std::string get_description_sid() const;
};
