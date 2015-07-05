#include "Feature.hpp"

class StoneMarker : public Feature
{
  public:
    StoneMarker();
    virtual Feature* clone() override;

    bool operator==(const StoneMarker& t) const;

    virtual uchar get_symbol() const override;

    virtual float get_hp_regeneration_multiplier() const override;
    virtual float get_ap_regeneration_multiplier() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

