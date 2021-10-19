#include "Amulet.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "Commands.hpp"
#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DecisionStrategyProperties.hpp"
#include "EngineConversion.hpp"
#include "MapUtils.hpp"
#include "NPCPickupDecisionStrategy.hpp"
#include "NPCUseEquipItemDecisionStrategy.hpp"
#include "Ring.hpp"
#include "Spellbook.hpp"
#include "Wand.hpp"
#include "WeaponManager.hpp"

using namespace std;

CommandPtr NPCPickupDecisionStrategy::decide(CreaturePtr creature, MapPtr map)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && map != nullptr)
  {
    CarryingCapacityCalculator ccc;
    uint burden_weight_oz = ccc.calculate_burdened_weight(creature);
    uint weight_carried_oz = creature->get_weight_carried();

    BurdenLevel bl = BurdenLevelConverter::to_burden_level(creature);
    TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

    // Creatures won't pick up if they're already burdened.
    if (tile != nullptr && bl == BurdenLevel::BURDEN_LEVEL_UNBURDENED)
    {
      IInventoryPtr inv = tile->get_items();
      string pickup_s = creature->get_decision_strategy()->get_property(DecisionStrategyProperties::DECISION_STRATEGY_PICKUP);
      bool pickup = true;

      if (!pickup_s.empty())
      {
        pickup = String::to_bool(pickup_s);
      }

      if (inv != nullptr)
      {
        list<ItemPtr>& items = inv->get_items_ref();
        CurrentCreatureAbilities cca;

        for (ItemPtr item : items)
        {
          // NPCs don't pick up shop items, this is too hazardous to their
          // health!
          // 
          // They also don't pick up items that will make them burdened.
          if (get<1>(CreatureUtils::can_pick_up(creature, item)) > 0 &&
              cca.can_see(creature) &&
              item != nullptr &&
             !item->get_unpaid() &&
              pickup &&
             (weight_carried_oz + item->get_total_weight().get_weight() < burden_weight_oz))
          {
            ItemType itype = item->get_type();

            if (itype == ItemType::ITEM_TYPE_WEAPON)
            {
              pu_cmd = get_pick_up_weapon_decision(creature, item);
            }
            else if (itype == ItemType::ITEM_TYPE_ARMOUR)
            {
              pu_cmd = get_pick_up_armour_decision(creature, item);
            }
            else if (itype == ItemType::ITEM_TYPE_AMULET)
            {
              pu_cmd = get_pick_up_amulet_decision(creature, item);
            }
            else if (itype == ItemType::ITEM_TYPE_RING)
            {
              pu_cmd = get_pick_up_ring_decision(creature, item);
            }
            else if (itype == ItemType::ITEM_TYPE_AMMUNITION)
            {
              pu_cmd = get_pick_up_ammunition_decision(creature, item);
            }
            else if (itype == ItemType::ITEM_TYPE_WAND)
            {
              pu_cmd = get_pick_up_wand_decision(creature, item);
            }
            else if (itype == ItemType::ITEM_TYPE_SPELLBOOK)
            {
              pu_cmd = get_pick_up_book_decision(creature, item);
            }
            else if (itype == ItemType::ITEM_TYPE_CURRENCY)
            {
              pu_cmd = std::make_unique<PickUpCommand>(item->get_id());
            }

            if (pu_cmd != nullptr)
            {
              return pu_cmd;
            }
          }
        }
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCPickupDecisionStrategy::get_pick_up_weapon_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    NPCUseEquipItemDecisionStrategy ue;

    if (ue.should_equip_weapon(creature, item))
    {
      pu_cmd = std::make_unique<PickUpCommand>(item->get_id());
    }
  }

  return pu_cmd;
}

CommandPtr NPCPickupDecisionStrategy::get_pick_up_armour_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    NPCUseEquipItemDecisionStrategy ue;

    if (ue.should_equip_wearable(creature, item))
    {
      pu_cmd = std::make_unique<PickUpCommand>(item->get_id());
    }
  }

  return pu_cmd;
}

CommandPtr NPCPickupDecisionStrategy::get_pick_up_amulet_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    AmuletPtr amulet = std::dynamic_pointer_cast<Amulet>(item);

    if (amulet != nullptr)
    {
      ItemPtr amulet_eq = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_NECK);
      NPCUseEquipItemDecisionStrategy ue;

      if (amulet->get_is_good() && ue.should_equip_wearable(creature, item))
      {
        pu_cmd = std::make_unique<PickUpCommand>(amulet->get_id());
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCPickupDecisionStrategy::get_pick_up_ring_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    RingPtr ring = std::dynamic_pointer_cast<Ring>(item);

    if (ring != nullptr)
    {
      ItemPtr f1 = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER);
      ItemPtr f2 = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER);
      NPCUseEquipItemDecisionStrategy ue;

      if (ring->get_is_good() &&
           ((f1 == nullptr || ue.should_equip_wearable(creature, item, EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER)) ||
            (f2 == nullptr || ue.should_equip_wearable(creature, item, EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER))))
      {
        pu_cmd = std::make_unique<PickUpCommand>(ring->get_id());
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCPickupDecisionStrategy::get_pick_up_ammunition_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    WeaponManager wm;
    WeaponPtr ranged = std::dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON));
    WeaponPtr eq_ammo = std::dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION));
    WeaponPtr ammo = std::dynamic_pointer_cast<Weapon>(item);

    // Only pick up ammo if it's compatible with the weapon slot, if the
    // creature doesn't have ammo currently equipped, and if the creature
    // doesn't know any spells.
    //
    // (basically, ensure that you can't pin spellcasters in a pickup loop
    //  by firing a ton of rocks, etc)
    if (wm.is_ranged_weapon_skill_type_compatible_with_ammunition(ranged, ammo) &&
        eq_ammo == nullptr &&
        creature->get_spell_knowledge_ref().count_spells_known() == 0)
    {
      pu_cmd = std::make_unique<PickUpCommand>(item->get_id());
    }
  }

  return pu_cmd;
}

CommandPtr NPCPickupDecisionStrategy::get_pick_up_wand_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;
  CurrentCreatureAbilities cca;

  // Creatures only pick up wands if they can speak - otherwise, evoking won't
  // work.
  if (creature != nullptr && item != nullptr && cca.can_speak(creature))
  {
    if (item && item->get_type() == ItemType::ITEM_TYPE_WAND)
    {
      Wand* wand = dynamic_cast<Wand*>(item.get());

      if (wand->get_charges().get_current() > 0 && wand->get_has_damage())
      {
        pu_cmd = std::make_unique<PickUpCommand>(wand->get_id());
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCPickupDecisionStrategy::get_pick_up_book_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;
  CurrentCreatureAbilities cca;

  // Creatures only pick up spellbooks if they can speak - otherwise, casting won't
  // work.
  if (creature != nullptr && item != nullptr && cca.can_speak(creature))
  {
    if (item && item->get_type() == ItemType::ITEM_TYPE_SPELLBOOK)
    {
      Spellbook* book = dynamic_cast<Spellbook*>(item.get());
      if (CreatureUtils::has_skill_for_spell(creature, book->get_spell_id()))
      {
        pu_cmd = std::make_unique<PickUpCommand>(book->get_id());
      }
    }
  }

  return pu_cmd;
}

