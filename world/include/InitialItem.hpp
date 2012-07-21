#pragma once
#include <string>
#include <map>
#include <vector>

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
    InitialItem(const std::string& new_item_id, const std::vector<std::string>& new_random_item_ids, const std::map<std::string, std::string>& new_racial_item_ids);

    void set_item_id(const std::string& new_item_id);
    std::string get_item_id() const;

    void set_random_item_ids(const std::vector<std::string>& new_random_item_ids);
    std::vector<std::string> get_random_item_ids() const;

    void set_racial_item_ids(const std::map<std::string, std::string>& new_racial_item_ids);
    std::map<std::string, std::string> get_racial_item_ids() const;

  protected:
    std::string item_id;
    std::vector<std::string> random_item_ids;
    std::map<std::string, std::string> racial_item_ids;
};


