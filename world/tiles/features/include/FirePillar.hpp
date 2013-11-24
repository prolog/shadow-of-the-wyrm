#pragma once
#include "Feature.hpp"

class FirePillar : public Feature
{
  public:
    FirePillar();
    virtual Feature* clone();

    virtual bool handle();
    virtual bool kick();
    virtual bool get_is_blocking() const;

    virtual uchar get_symbol() const;

  protected:
    virtual std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
