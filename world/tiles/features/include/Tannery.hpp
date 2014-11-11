#include "Feature.hpp"

class Tannery : public Feature
{
  public:
    Tannery();
    virtual Feature* clone() override;

    bool operator==(const Tannery& t) const;

    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
