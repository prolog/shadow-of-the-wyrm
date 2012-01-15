#pragma once
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include "EquipmentTypes.hpp"
#include "ItemTypes.hpp"
#include "Weight.hpp"

class Item
{
  public:
    Item();
    ~Item();
    
    void set_id(const std::string& new_id);
    std::string get_id() const;
    
    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;
    
    void set_weight(const Weight& new_weight);
    Weight get_weight() const;
    
    void set_worn_location(const EquipmentWornLocation new_worn_location);
    EquipmentWornLocation get_worn_location() const;
    
    void set_status(const ItemStatus new_status);
    ItemStatus get_status() const;
    
  protected:
    std::string id;
    std::string description_sid;
    Weight weight;
    EquipmentWornLocation worn_location;
    ItemStatus status;
};

typedef boost::shared_ptr<Item> ItemPtr;
typedef std::map<std::string, ItemPtr> ItemMap;
