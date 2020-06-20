#pragma once
#include "Ammunition.hpp"
#include "Weapon.hpp"
#include "XMLWearableReader.hpp"

// Classes for reading in melee, ranged, and ammunition.

// Class for parsing weapons into a given shared pointer, from a node
// that conforms to the Weapon XML node type.
class XMLWeaponsReader : public XMLWearableReader
{
  public:
    XMLWeaponsReader();
    ~XMLWeaponsReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(WeaponPtr weapon, GenerationValues& gv, const XMLNode& ranged_weapon_node);
};

class XMLAmmunitionReader : public XMLWeaponsReader
{
  public:
    XMLAmmunitionReader();
    ~XMLAmmunitionReader();
    
  protected:
    friend class XMLItemsReader;
    void parse(WeaponPtr ammunition, GenerationValues& gv, const XMLNode& ammunition_node);
};

