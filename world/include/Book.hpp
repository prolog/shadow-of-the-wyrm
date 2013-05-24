#pragma once
#include "Readable.hpp"

class Book : public Readable
{
  public:
    Book();
    ~Book();

    bool operator==(const Book& book) const;
    
    bool destroy_on_read() const;

    void set_spell_id(const std::string& new_spell_id);
    std::string get_spell_id() const;
    
    Item* clone();

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    std::string spell_id;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Book> BookPtr;
