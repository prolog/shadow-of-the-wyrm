#pragma once
#include "Feature.hpp"

// Benches are made of iron, and increase healing rates while sitting by
// a little.
class Bench : public Feature
{
  public:
    Bench();
    virtual Feature* clone() override;

    virtual bool handle(std::shared_ptr<Tile>, std::shared_ptr<Creature>) override;
    virtual bool kick() override;
    
    virtual uchar get_symbol() const override;

  protected:
    virtual std::string get_description_sid() const override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
