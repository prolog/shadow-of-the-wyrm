#include "ArmourCodexDescriber.hpp"
#include "CodexDescriberFactory.hpp"
#include "CodexDescriber.hpp"
#include "ConsumableCodexDescriber.hpp"
#include "SpellbookCodexDescriber.hpp"
#include "WandCodexDescriber.hpp"
#include "WeaponCodexDescriber.hpp"
#include "WearableCodexDescriber.hpp"
#include "Armour.hpp"

using namespace std;

CodexDescriberPtr CodexDescriberFactory::create_codex_describer(const ItemPtr item)
{
  CodexDescriberPtr desc;

  if (item != nullptr)
  {
    ItemType itype = item->get_type();

    switch (itype)
    {
      case ItemType::ITEM_TYPE_AMMUNITION:
      case ItemType::ITEM_TYPE_WEAPON:
      {
        WeaponPtr weapon = dynamic_pointer_cast<Weapon>(item);
        desc = std::make_shared<WeaponCodexDescriber>(weapon);
        break;
      }
      case ItemType::ITEM_TYPE_SPELLBOOK:
      {
        SpellbookPtr spellbook = dynamic_pointer_cast<Spellbook>(item);
        desc = std::make_shared<SpellbookCodexDescriber>(spellbook);
        break;
      }
      case ItemType::ITEM_TYPE_FOOD:
      case ItemType::ITEM_TYPE_PLANT:
      case ItemType::ITEM_TYPE_POTION:
      {
        ConsumablePtr consumable = dynamic_pointer_cast<Consumable>(item);
        desc = std::make_shared<ConsumableCodexDescriber>(consumable);
        break;
      }
      case ItemType::ITEM_TYPE_RING:
      case ItemType::ITEM_TYPE_AMULET:
      {
        WearablePtr wearable = dynamic_pointer_cast<Wearable>(item);
        desc = std::make_shared<WearableCodexDescriber>(wearable);
        break;
      }
      case ItemType::ITEM_TYPE_ARMOUR:
      {
        ArmourPtr armour = dynamic_pointer_cast<Armour>(item);
        desc = std::make_shared<ArmourCodexDescriber>(armour);
        break;
      }
      case ItemType::ITEM_TYPE_WAND:
      {
        WandPtr wand = dynamic_pointer_cast<Wand>(item);
        desc = std::make_shared<WandCodexDescriber>(wand);
        break;
      }
      case ItemType::ITEM_TYPE_BOAT:
      case ItemType::ITEM_TYPE_CURRENCY:
      case ItemType::ITEM_TYPE_MISC:
      case ItemType::ITEM_TYPE_STAFF:
      case ItemType::ITEM_TYPE_TOOL:
      default:
        desc = std::make_shared<CodexDescriber>(item);
    }

  }

  return desc;
}

