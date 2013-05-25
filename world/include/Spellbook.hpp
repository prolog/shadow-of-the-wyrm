#pragma once
#include "Readable.hpp"

class Spellbook : public Readable
{
  public:
    Spellbook();
    ~Spellbook();

    bool operator==(const Spellbook& book) const;
    
    bool destroy_on_read() const;

    void set_spell_id(const std::string& new_spell_id);
    std::string get_spell_id() const;

    void set_difficulty(const int new_difficulty);
    int get_difficulty() const;
    
    Item* clone();

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    std::string spell_id;
    int difficulty;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Spellbook> SpellbookPtr;
