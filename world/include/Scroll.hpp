#pragma once
#include "Readable.hpp"

class Scroll : public Readable
{
  public:
    Scroll();
    ~Scroll();
    
    bool destroy_on_read() const;
    
    Item* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef std::shared_ptr<Scroll> ScrollPtr;
