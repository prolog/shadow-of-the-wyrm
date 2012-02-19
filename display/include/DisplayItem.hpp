#pragma once
#include <map>
#include <string>
#include <vector>
#include "DisplayItemType.hpp"
#include "EquipmentTypes.hpp"
#include "ItemTypes.hpp"

// A DisplayItem contains the relevant details of an item for the Display
// to use in its inventory and equipment management routines.
class DisplayItem
{
  public:
    DisplayItem();
    ~DisplayItem();

    void set_description(const std::string& new_description);
    std::string get_description();
    
    // Additional status-related items go here.
    
  protected:
    std::string description;
};

// Data types used by the Display
typedef std::map<EquipmentWornLocation, DisplayItem> DisplayEquipmentMap;
typedef std::map<DisplayItemTypePtr, std::vector<DisplayItem> > DisplayInventoryMap;
