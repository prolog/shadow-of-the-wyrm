#pragma once
#include "Readable.hpp"

class Book : public Readable
{
  public:
    Book();
    ~Book();
    
    bool destroy_on_read() const;
    
    Item* clone();
};

typedef boost::shared_ptr<Book> BookPtr;
