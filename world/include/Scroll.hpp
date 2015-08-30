#pragma once
#include "Readable.hpp"

class Scroll : public Readable
{
  public:
    Scroll();
    ~Scroll();
    
    bool destroy_on_read() const override;
    
    Item* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using ScrollPtr = std::shared_ptr<Scroll>;
