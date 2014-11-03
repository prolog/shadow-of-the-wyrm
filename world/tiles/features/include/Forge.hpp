#include "Feature.hpp"

class Forge : public Feature
{
  public:
    Forge();
    virtual Feature* clone() override;

    bool operator==(const Forge& b) const;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
