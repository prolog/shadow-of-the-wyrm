#pragma once
#include "Readable.hpp"

class Book : public Readable
{
  public:
    Book();
    ~Book();
    
    bool destroy_on_read() const;
    
    Item* clone();

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Book> BookPtr;
