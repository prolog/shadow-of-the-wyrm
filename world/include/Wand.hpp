#pragma once
#include "Item.hpp"

class Wand : public Item
{
  public:
    Wand();
    ~Wand();
    
    Item* clone();

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Wand> WandPtr;
