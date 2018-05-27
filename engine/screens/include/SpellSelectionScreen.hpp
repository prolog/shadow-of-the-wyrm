#pragma once
#include <map>
#include <string>
#include "Creature.hpp"
#include "Screen.hpp"
#include "Display.hpp"
#include "Spell.hpp"
#include "SpellTypes.hpp"

class SpellScreenDisplayStrategy
{
  public:
    virtual bool display_spell(const Spell& spell) const = 0;
};

class DefaultSpellScreenDisplayStrategy : public SpellScreenDisplayStrategy
{
  public:
    bool display_spell(const Spell& spell) const;
};

class SituationTypeSpellScreenDisplayStrategy : public SpellScreenDisplayStrategy
{
  public:
    SituationTypeSpellScreenDisplayStrategy(const SpellSituationType new_sst);

    bool display_spell(const Spell& spell) const;

  protected:
    SpellSituationType sst;
};

using SpellScreenDisplayStrategyPtr = std::shared_ptr<SpellScreenDisplayStrategy>;

class SpellSelectionScreen : public Screen
{
  public:
    SpellSelectionScreen(DisplayPtr new_display, CreaturePtr new_creature, SpellScreenDisplayStrategyPtr sds);

    std::string get_selected_spell(const char selection) const;

  protected:
    void initialize() override;

    std::vector<std::map<char, std::string>> screen_selection_to_spell_id_map;
    CreaturePtr creature;
    SpellScreenDisplayStrategyPtr strategy;
};
