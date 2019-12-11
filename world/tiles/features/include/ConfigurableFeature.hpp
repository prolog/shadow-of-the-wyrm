#pragma once
#include "Feature.hpp"

class ConfigurableFeature : public Feature
{
  public:
    ConfigurableFeature(const Symbol& new_symbol);
    ConfigurableFeature(const Symbol& new_symbol, MaterialType mt, const std::string& new_description_sid);

    bool operator==(const ConfigurableFeature& cf) const;

    virtual Feature* clone() override;

    virtual void set_colour(const Colour colour);
    virtual Colour get_colour() const;

    virtual void set_description_sid(const std::string& new_description_sid);

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    std::string description_sid;
    Colour colour;
  
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
