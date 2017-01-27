#pragma once
#include <vector>
#include "ItemTypes.hpp"
#include "RarityTypes.hpp"

class ItemGenerationConstraints
{
  public:
    ItemGenerationConstraints();
    ItemGenerationConstraints(const int new_min_danger_level, const int new_max_danger_level, const Rarity new_rarity, const std::vector<ItemType>& new_item_type_restrictions, const int new_min_value);

    void set_min_danger_level(const int new_min_danger_level);
    int get_min_danger_level() const;

    void set_max_danger_level(const int new_max_danger_level);
    int get_max_danger_level() const;

    void set_rarity(const Rarity new_rarity);
    Rarity get_rarity() const;

    void set_item_type_restrictions(const std::vector<ItemType>& new_item_type_restrictions);
    std::vector<ItemType> get_item_type_restrictions() const;

    void set_min_value(const int new_min_value);
    int get_min_value() const;

  protected:
    int min_danger_level;
    int max_danger_level;
    Rarity rarity;
    std::vector<ItemType> item_type_restrictions;
    int min_value;
};

