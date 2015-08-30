#pragma once
#include <map>
#include <string>
#include <vector>
#include "DisplayItemType.hpp"
#include "EquipmentTypes.hpp"
#include "ItemTypes.hpp"

using DisplayItemFlagsVec = std::vector<TextColour>;

// A DisplayItem contains the relevant details of an item for the Display
// to use in its inventory and equipment management routines.
class DisplayItem
{
  public:
    DisplayItem();
    ~DisplayItem();

    void set_description(const std::string& new_description);
    std::string get_description() const;

    void set_additional_description(const std::string& new_additional_description);
    std::string get_additional_description() const;

    void set_flags(const DisplayItemFlagsVec& new_flags);
    DisplayItemFlagsVec get_flags() const;

    void set_colour(const Colour new_colour);
    Colour get_colour() const;
    
    void set_id(const std::string& new_id);
    std::string get_id() const;
    
    // Additional status-related items go here.
  protected:
    std::string description;
    std::string additional_description;
    std::vector<std::pair<std::string, Colour>> flags;
    Colour colour;
    std::string id;
};

// Data types used by the Display
using DisplayEquipmentMap = std::map<EquipmentWornLocation, DisplayItem>;
using DisplayInventoryMap = std::map<DisplayItemType, std::vector<DisplayItem>>;
