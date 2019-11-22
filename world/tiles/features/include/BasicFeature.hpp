#pragma once
#include "Feature.hpp"

// This class is used for creating features that have some sort of
// description, but can't be interacted with at all..
class BasicFeature : public Feature
{
  public:
    BasicFeature();
    BasicFeature(const MaterialType mt, const uchar new_symbol, const Colour new_colour, const std::string& new_description_sid);

    virtual Feature* clone() override;

    bool operator==(const BasicFeature& bf) const;

    virtual void set_symbol(const uchar new_symbol);
    virtual uchar get_symbol() const override;

    virtual void set_colour(const Colour new_colour);
    virtual Colour get_colour() const override;
    
    virtual void set_description_sid(const std::string& new_description_sid);

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    virtual std::string get_description_sid() const;

    uchar symbol;
    Colour colour;
    std::string description_sid;
  
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
