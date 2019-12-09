#pragma once
#include "Feature.hpp"

class Tannery : public Feature
{
  public:
    Tannery(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const Tannery& t) const;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
