#pragma once
#include "Weapon.hpp"

class Ammunition : public RangedWeapon
{
  public:
    Ammunition();
    ~Ammunition();
    bool operator==(const Ammunition& ammo) const;

    virtual EquipmentWornLocation get_worn_location() const;
    
    // TODO: Add a function to let me figure out if the ammunition works with the ranged weapon...probbaly put this in
    // MeleeWeapon, and delete the Ammunition class.
    
    Item* clone();

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);
    
  protected:
    // Whether the ammunition requires a ranged weapon.  Some (arrows, bolts) do.
    // Others (clubs, rocks) don't.
    bool requires_ranged_weapon;

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Ammunition> AmmunitionPtr;
