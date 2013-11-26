#pragma once
#include "Pew.hpp"

class EastWestPew : public Pew
{
  public:
    EastWestPew();
    virtual Feature* clone() override;


    uchar get_symbol() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
