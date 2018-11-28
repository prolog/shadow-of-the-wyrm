#include "Feature.hpp"

class Pulper : public Feature
{
  public:
    Pulper();
    virtual Feature* clone() override;

    bool operator==(const Pulper& p) const;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
