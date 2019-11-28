#pragma once
#include "common.hpp"
#include "Colours.hpp"
#include "ISerializable.hpp"
#include "SpritesheetLocation.hpp"

class Symbol : public ISerializable
{
  public:
    Symbol();
    Symbol(const uchar new_symbol, const Colour new_colour, const SpritesheetLocation& new_spritesheet_location);
    bool operator==(const Symbol& sym) const;

    void set_symbol(const uchar new_symbol);
    uchar get_symbol() const;

    void set_colour(const Colour new_colour);
    Colour get_colour() const;

    bool get_uses_spritesheet() const;
    void set_spritesheet_location(const SpritesheetLocation& new_spritesheet_location);
    SpritesheetLocation get_spritesheet_location() const;
    SpritesheetLocation& get_spritesheet_location_ref();

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    uchar symbol;
    Colour colour;
    SpritesheetLocation spritesheet_location;

  private:
    ClassIdentifier internal_class_identifier() const override;
};