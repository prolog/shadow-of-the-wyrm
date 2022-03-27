#include "CompanionDeityDecisionStrategyHandler.hpp"
#include "CoordUtils.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreatureUtils.hpp"
#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "DivineCompanionCalculator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HostilityManager.hpp"
#include "MapUtils.hpp"
#include "ReligionManager.hpp"

using std::string;

const int CompanionDeityDecisionStrategyHandler::MIN_PIETY_FOR_COMPANION = 3000;

CompanionDeityDecisionStrategyHandler::CompanionDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

std::unique_ptr<DeityDecisionStrategyHandler> CompanionDeityDecisionStrategyHandler::clone()
{
  std::unique_ptr<DeityDecisionStrategyHandler> handler = std::make_unique<CompanionDeityDecisionStrategyHandler>(*this);
  return handler;
}

bool CompanionDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  if (creature)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    CreatureMap creatures = CreatureUtils::get_followers(creature, map);
    auto adj_avail = MapUtils::get_adjacent_tiles_to_creature(map, creature);

    if (creatures.empty() && std::find_if(adj_avail.begin(), adj_avail.end(), [](auto& p) { return p.second->has_creature() == false; }) != adj_avail.end())
    {
      ReligionManager rm;
      int piety = rm.get_piety_for_active_deity(creature);

      if (piety > MIN_PIETY_FOR_COMPANION)
      {
        decision = CreatureUtils::get_followers(creature, map).empty();
      }
    }
  }

  return decision;
}

DeityDecisionImplications CompanionDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature)
  {
    Game& game = Game::instance();
    MapPtr map = game.get_current_map();
    CreatureGenerationManager cgm;
    int clvl = creature->get_level().get_current() + 2;
    int max_clvl = clvl + 10;

    auto generation_list = cgm.generate_creature_generation_map({ map->get_terrain_type() }, true /* assume permanent */, map && map->is_islet(), clvl, max_clvl, Rarity::RARITY_COMMON, {}).get();

    if (generation_list.empty())
    {
      // Player gets an ancient beast OwO
      // Fudge the generation list so that ancient beasts will always generate
      // regardless of what kind of map the player is actually on.
      generation_list = cgm.generate_ancient_beasts(max_clvl, MapType::MAP_TYPE_UNDERWORLD, TileType::TILE_TYPE_DUNGEON_COMPLEX).get();
    }

    CreaturePtr gen_creature = cgm.generate_creature(game.get_action_manager_ref(), generation_list, map);

    if (gen_creature != nullptr)
    {
      gen_creature->set_leader_and_at_ease(creature->get_id());
      set_companion_bonuses(creature, gen_creature);

      HostilityManager hm;
      hm.set_hostility_to_player(gen_creature, false);

      auto avail_map = MapUtils::get_available_adjacent_tiles_to_creature(map, creature, gen_creature);

      if (!avail_map.empty())
      {
        auto pair = avail_map.begin();
        Coordinate gc = CoordUtils::get_new_coordinate(map->get_location(creature->get_id()), pair->first);
        GameUtils::add_new_creature_to_map(game, gen_creature, map, gc);
      }
    }
  }

  return get_deity_decision_implications(creature, tile);
}

void CompanionDeityDecisionStrategyHandler::set_companion_bonuses(CreaturePtr creature, CreaturePtr companion)
{
  if (companion != nullptr)
  {
    DivineCompanionCalculator dcc(creature);
    Damage d = companion->get_base_damage();

    Statistic calc_hp = dcc.calculate_hp(companion->get_hit_points());
    Statistic calc_ap = dcc.calculate_ap(companion->get_arcana_points());
    int damage_mod = dcc.calculate_damage_modifier(companion, d);
    d.set_modifier(damage_mod);

    companion->set_hit_points(calc_hp);
    companion->set_arcana_points(calc_ap);
    companion->set_base_damage(d);
    companion->set_breathes(BreatheType::BREATHE_TYPE_ALL);
  }
}

int CompanionDeityDecisionStrategyHandler::get_piety_amount() const
{
  return 2000;
}

string CompanionDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_COMPANION;
}
