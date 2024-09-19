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
    virtual ~SpellScreenDisplayStrategy() = default;

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

using SpellScreenDisplayStrategyPtr = std::unique_ptr<SpellScreenDisplayStrategy>;

class SpellSelectionScreen : public Screen
{
  public:
    SpellSelectionScreen(DisplayPtr new_display, CreaturePtr new_creature, SpellScreenDisplayStrategy* sds);

    std::string get_selected_spell(const char selection) const;

  protected:
    void initialize() override;
    std::vector<Spell> get_spells_in_display_order(const SpellMap& spells);
    static bool sort_spells_for_display(const Spell& s1, const Spell& s2);

    std::vector<std::map<char, std::string>> screen_selection_to_spell_id_map;
    CreaturePtr creature;
    SpellScreenDisplayStrategy* strategy;
};
