#pragma once
#include "Feature.hpp"

// JCD SYMBOL SPRITESHEET FIXME
//
// Fold this back into regular features once symbol/desc are per-feature.

// This class is used for creating features that have some sort of
// description, but can't be interacted with at all..
class BasicFeature : public Feature
{
  public:
    BasicFeature(const Symbol& new_symbol);
    BasicFeature(const Symbol& new_symbol, MaterialType mt, const std::string& new_description_sid);

    virtual Feature* clone() override;

    virtual void set_colour(const Colour colour);
    virtual Colour get_colour() const;

    bool operator==(const BasicFeature& bf) const;

    virtual void set_description_sid(const std::string& new_description_sid);

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const;

    std::string description_sid;
    Colour colour;
  
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
