#pragma once
#include "Pew.hpp"
#include "Symbol.hpp"

// JCD FIXME SYMBOL SPRITESHEET
// This can be merged with Pew when done
class EastWestPew : public Pew
{
  public:
    EastWestPew(const Symbol& new_symbol);
    virtual Feature* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
