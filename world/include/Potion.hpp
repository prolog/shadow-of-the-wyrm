#pragma once
#include "Consumable.hpp"
#include "Damage.hpp"

class Potion : public Consumable
{
  public:
    Potion();
    ~Potion();
    bool operator==(const Potion& p) const;
    
    ItemType get_type() const;
    Item* clone();

    void set_has_damage(const bool new_has_damage);
    bool get_has_damage() const;

    void set_damage(const Damage& new_damage);
    Damage get_damage() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    bool has_damage;
    Damage damage;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Potion> PotionPtr;
