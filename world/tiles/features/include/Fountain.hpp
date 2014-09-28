#include "Feature.hpp"

class Fountain : public Feature
{
  public:
    Fountain();
    virtual Feature* clone() override;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
