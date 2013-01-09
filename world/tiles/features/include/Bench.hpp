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

    virtual std::string get_description_sid() const;
    
    virtual uchar get_symbol() const;

  private:
    ClassIdentifier internal_class_identifier() const;
};
