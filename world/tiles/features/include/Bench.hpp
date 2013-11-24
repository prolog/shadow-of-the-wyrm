#pragma once
#include "Feature.hpp"

// Benches are made of iron, and increase healing rates while sitting by
// a little.
class Bench : public Feature
{
  public:
    Bench();
    virtual Feature* clone();

    virtual bool handle();
    virtual bool kick();
    
    virtual uchar get_symbol() const;

  protected:
    virtual std::string get_description_sid() const;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
