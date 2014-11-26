#include "Feature.hpp"

class WheelAndLoom : public Feature
{
  public:
    WheelAndLoom();
    virtual Feature* clone() override;

    bool operator==(const WheelAndLoom& j) const;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

