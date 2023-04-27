#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "Game.hpp"
#include "GrantSpellDeityDecisionStrategyHandler.hpp"
#include "RNG.hpp"
#include "SpellbookReadStrategy.hpp"

using std::string;
using std::vector;

GrantSpellDeityDecisionStrategyHandler::GrantSpellDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

std::unique_ptr<DeityDecisionStrategyHandler> GrantSpellDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<GrantSpellDeityDecisionStrategyHandler>(*this);
  return handler;
}

bool GrantSpellDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  if (creature)
  {
    Statistic ap = creature->get_arcana_points();

    // Max AP less than smallest divine spell?
    Game& game = Game::instance();
    const auto& spells = game.get_spells_ref();

    for (const auto& s_pair : spells)
    {
      SkillType sphere = s_pair.second.get_magic_category();

      if (sphere == SkillType::SKILL_MAGIC_DIVINE && s_pair.second.get_ap_cost() <= static_cast<uint>(ap.get_base()))
      {
        return true;
      }
    }
  }

  return false;
}

DeityDecisionImplications GrantSpellDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature)
  {
    Statistic ap = creature->get_arcana_points();
    vector<Spell> potential_spells;

    // Max AP less than smallest divine spell?
    Game& game = Game::instance();
    const auto& spells = game.get_spells_ref();

    for (const auto& s_pair : spells)
    {
      SkillType sphere = s_pair.second.get_magic_category();

      if (sphere == SkillType::SKILL_MAGIC_DIVINE && s_pair.second.get_ap_cost() <= static_cast<uint>(ap.get_base()))
      {
        potential_spells.push_back(s_pair.second);
      }
    }

    std::shuffle(potential_spells.begin(), potential_spells.end(), RNG::get_engine());

    if (!potential_spells.empty())
    {
      Spell spell = potential_spells.at(0);
      SpellbookReadStrategy srs;
      int creature_level = creature->get_level().get_current();
      srs.add_spell_castings(creature, spell.get_spell_id(), RNG::range(creature_level * 2, creature_level * 3));
    }
  }

  return get_deity_decision_implications(creature, tile);
}

int GrantSpellDeityDecisionStrategyHandler::get_piety_amount() const
{
  return 1000;
}

string GrantSpellDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_LEARN_SPELL;
}
