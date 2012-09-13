#pragma once
#include "Item.hpp"

// A class that inherits from items.  All readable items (books, scrolls,
// etc) should inherit from this class.
class Readable : public Item
{
  public:
    // Scrolls are consumed when used.  Spellbooks are not, though they may be destroyed as part
    // of the overall read logic.
    virtual bool destroy_on_read() const = 0;
    
  protected:
    // protected so that the class can't actually be instantiated
    // directly - it should only be instantiated as one of its
    // subclasses.
    Readable();
    ~Readable();
};

typedef boost::shared_ptr<Readable> ReadablePtr;

