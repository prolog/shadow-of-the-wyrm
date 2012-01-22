#include "ItemManager.hpp"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}

bool ItemManager::pick_up(CreaturePtr creature, ItemPtr item)
{
  return true;
}

bool ItemManager::drop(CreaturePtr creature, ItemPtr item)
{
  return true;
}

// Add the item to the creature's list of equipped items.
bool ItemManager::equip(CreaturePtr creature, ItemPtr item)
{
  return true;
}
