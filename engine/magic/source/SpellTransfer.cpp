#include "SpellTransfer.hpp"
#include "ItemProperties.hpp"

using namespace std;

bool SpellTransfer::to_item(const Spell& spell, ItemPtr item)
{
  bool trans = false;

  if (item != nullptr)
  {
    item->set_additional_property(ItemProperties::ITEM_PROPERTIES_REPLACEMENT_SID, spell.get_spell_name_sid());

    map<string, string> properties = spell.get_properties();
    for (const auto& s_pair : properties)
    {
      item->set_additional_property(s_pair.first, s_pair.second);
    }

    item->set_effect_type(spell.get_effect());
    item->set_modifier(spell.get_modifier());

    trans = true;
  }

  return trans;
}

bool SpellTransfer::to_scroll(const Spell& spell, ScrollPtr scroll)
{
  return to_item(spell, scroll);
}

bool SpellTransfer::to_potion(const Spell& spell, PotionPtr potion)
{
  bool trans = false;

  if (potion != nullptr)
  {
    to_item(spell, potion);

    if (spell.get_has_damage())
    {
      potion->set_damage(spell.get_damage());
      potion->set_has_damage(true);
    }

    trans = true;
  }

  return trans;
}

bool SpellTransfer::to_wand(const Spell& spell, WandPtr wand)
{
  bool trans = false;

  if (wand != nullptr)
  {
    to_item(spell, wand);

    if (spell.get_has_damage())
    {
      wand->set_damage(spell.get_damage());
      wand->set_has_damage(true);
    }

    wand->set_spell_colour(spell.get_colour());
    wand->set_spell_shape_type(spell.get_shape().get_spell_shape_type());
    wand->set_range(spell.get_range());
    wand->set_radius(spell.get_shape().get_radius());

    trans = true;
  }

  return trans;
}