#pragma once
#include "Feature.hpp"

// A number of lightweight regular statues that can be generated
// by the StatueGenerator.
class RegularStatue : public Feature
{
  public:
    RegularStatue();

    virtual bool handle();
    virtual bool kick();
    virtual bool get_is_blocking() const;

    virtual uchar get_symbol() const;

    // get_description_sid() not implemented because this is an abstract
    // parent class.

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};


class PetrifiedCorpseStatue : public RegularStatue
{
  public:
    PetrifiedCorpseStatue();

    virtual Feature* clone();
    
  protected:
    std::string get_description_sid() const;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};


