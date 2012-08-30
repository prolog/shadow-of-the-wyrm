#pragma once
#include <string>
#include <map>
#include <vector>
#include "Dice.hpp"

// An initial item is generated on character creation based on the details in this class.
//
// The "item_id" is the base item ID, which is used if there is no random or racial override.
//
// If at least one random item ID is provided, the final item ID will be one of the IDs from this
// collection - racial overrides will not be considered.
//
// If there is a racial override for the character's race, the racial override will override the
// base value.
class InitialItem
{
  public:
    InitialItem();
    InitialItem(const std::string& new_item_id, const Dice& quant, const std::vector<std::pair<std::string, Dice> >& new_random_item_ids, const std::map<std::string, std::pair<std::string, Dice> >& new_racial_item_ids);

    void set_item_id(const std::string& new_item_id);
    std::string get_item_id() const;
    
    void set_item_quantity(const Dice& new_item_quantity);
    Dice get_item_quantity() const;

    void set_random_item_ids(const std::vector<std::pair<std::string, Dice> >& new_random_item_ids);
    std::vector<std::pair<std::string, Dice> > get_random_item_ids() const;

    void set_racial_item_ids(const std::map<std::string, std::pair<std::string, Dice> >& new_racial_item_ids);
    std::map<std::string, std::pair<std::string, Dice> > get_racial_item_ids() const;

  protected:
    std::string item_id;
    Dice item_quantity;
    std::vector<std::pair<std::string, Dice> > random_item_ids;
    std::map<std::string, std::pair<std::string, Dice> > racial_item_ids;
};


