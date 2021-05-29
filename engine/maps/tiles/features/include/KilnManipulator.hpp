#pragma once
#include "ActionManager.hpp"
#include "FeatureManipulator.hpp"

class KilnManipulator : public FeatureManipulator
{
  public:
    KilnManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

  protected:
    bool check_for_clay(CreaturePtr creature);
    ItemPtr get_item(const std::string& item_base_id, CreaturePtr creature);
    
    using ItemVerifier = bool (KilnManipulator::*)(CreaturePtr);

    bool notify_on_first_uncraftable_item(CreaturePtr creature);

    bool verify_item_requirements(const std::vector<std::string>& required_item_ids, const std::string& crafted_item_id, const bool add_message, CreaturePtr creature);
    bool verify_clay_pot(CreaturePtr creature);
    bool verify_clay_shot(CreaturePtr creature);
    bool verify_fire_bomb(CreaturePtr creature);
    bool verify_shadow_bomb(CreaturePtr creature);

    bool create_clay_item(ItemVerifier v, const std::vector<std::string>& required_item_ids, const std::string& crafted_item_id, const int rng_min, const int rng_max, CreaturePtr creature);
    bool create_clay_pot(CreaturePtr creature);
    bool create_clay_shot(CreaturePtr creature);
    bool create_fire_bomb(CreaturePtr creature);
    bool create_shadow_bomb(CreaturePtr creature);

    std::map<int, std::pair<bool (KilnManipulator::*)(CreaturePtr), ItemVerifier>> crafting_functions;
};

