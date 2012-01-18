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
    
    virtual void set_id(const std::string& new_id);
    virtual std::string get_id() const;
    
    virtual void set_description_sid(const std::string& new_description_sid);
    virtual std::string get_description_sid() const;
    
    virtual void set_weight(const Weight& new_weight);
    virtual Weight get_weight() const;
    
    virtual void set_worn_location(const EquipmentWornLocation new_worn_location);
    virtual EquipmentWornLocation get_worn_location() const;
    
    virtual void set_status(const ItemStatus new_status);
    virtual ItemStatus get_status() const;
    
    virtual void set_artifact(const bool new_artifact);
    virtual bool get_artifact() const;
    
    virtual void set_type(const ItemType type);
    ItemType get_type() const;
    
  protected:
    std::string id;
    std::string description_sid;
    Weight weight;
    EquipmentWornLocation worn_location;
    ItemStatus status;
    bool artifact;
    ItemType type;
};

typedef boost::shared_ptr<Item> ItemPtr;
typedef std::map<std::string, ItemPtr> ItemMap;
