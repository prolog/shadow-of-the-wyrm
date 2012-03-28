#pragma once
#include "Feature.hpp"

class Pew : public Feature
{
  public:
    Pew();

    virtual bool handle();
    virtual bool kick();

    virtual uchar get_symbol() const;
};
