#include "CodexDescriberFactory.hpp"
#include "CodexDescriber.hpp"
#include "ConsumableCodexDescriber.hpp"
#include "SpellbookCodexDescriber.hpp"
#include "WeaponCodexDescriber.hpp"

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
        desc = std::make_shared<WeaponCodexDescriber>(item);
        break;
      case ItemType::ITEM_TYPE_SPELLBOOK:
        desc = std::make_shared<SpellbookCodexDescriber>(item);
        break;
      case ItemType::ITEM_TYPE_FOOD:
      case ItemType::ITEM_TYPE_PLANT:
      case ItemType::ITEM_TYPE_POTION:
        desc = std::make_shared<ConsumableCodexDescriber>(item);
        break;
      case ItemType::ITEM_TYPE_AMULET:
      case ItemType::ITEM_TYPE_ARMOUR:
      case ItemType::ITEM_TYPE_BOAT:
      case ItemType::ITEM_TYPE_CURRENCY:
      case ItemType::ITEM_TYPE_MISC:
      case ItemType::ITEM_TYPE_RING:
      case ItemType::ITEM_TYPE_STAFF:
      case ItemType::ITEM_TYPE_TOOL:
      case ItemType::ITEM_TYPE_WAND:
      default:
        desc = std::make_shared<CodexDescriber>(item);
    }

  }

  return desc;
}

