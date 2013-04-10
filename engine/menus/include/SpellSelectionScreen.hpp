#pragma once
#include <map>
#include <string>
#include "Creature.hpp"
#include "Menu.hpp"
#include "Display.hpp"

class SpellSelectionScreen : public Menu
{
  public:
    SpellSelectionScreen(DisplayPtr new_display, CreaturePtr new_creature);

  protected:
    void initialize();

    std::map<int, std::string> menu_selection_to_spell_id_map;
    CreaturePtr creature;
};
