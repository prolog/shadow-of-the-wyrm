#pragma once
#include "Readable.hpp"

class Scroll : public Readable
{
  public:
    Scroll();
    ~Scroll();
    
    bool destroy_on_read() const;
    
    Item* clone();
};

typedef boost::shared_ptr<Scroll> ScrollPtr;
