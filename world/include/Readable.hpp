#pragma once
#include "Item.hpp"

// A class that inherits from items.  All readable items (books, scrolls,
// etc) should inherit from this class.
class Readable : public Item
{
  public:
    bool operator==(const Readable& r) const;

    // Scrolls are consumed when used.  Spellbooks are not, though they may be destroyed as part
    // of the overall read logic.  Tomes should not be destroyed 
    // (they're just regular books).
    virtual bool destroy_on_read() const = 0;

    virtual void set_text_sid(const std::string& new_text_sid);
    virtual std::string get_text_sid() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);
    
  protected:
    // protected so that the class can't actually be instantiated
    // directly - it should only be instantiated as one of its
    // subclasses.
    Readable();
    ~Readable();

    std::string text_sid;
};

typedef boost::shared_ptr<Readable> ReadablePtr;

