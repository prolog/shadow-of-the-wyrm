#pragma once
#include "Pew.hpp"

class EastWestPew : public Pew
{
  public:
    EastWestPew();

    uchar get_symbol() const;
};
