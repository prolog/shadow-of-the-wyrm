#pragma once
#include "IActionManager.hpp"
#include "TextDisplayFormatter.hpp"

// Displays information about a particular creature.
class BestiaryAction : public IActionManager
{
  public:
    BestiaryAction();

    ActionCostValue display_creature_information(CreaturePtr creature, const std::string& creature_search_text, CreaturePtr bestiary_creature_instance = nullptr) const;
    void display_bestiary_information(CreaturePtr beast) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    // Figure out what creature best matches the search text, if anything
    // matches at all.
    CreaturePtr get_bestiary_creature(const std::string& creature_search_text) const;

    void display_race_information(std::vector<std::pair<Colour, std::string>>& bestiary_text, const TextDisplayFormatter& tdf, CreaturePtr beast) const;
    void display_deity_information(std::vector<std::pair<Colour, std::string>>& bestiary_text, const TextDisplayFormatter& tdf, CreaturePtr beast) const;
    void display_id_details(std::vector<std::pair<Colour, std::string>>& bestiary_text, const TextDisplayFormatter& tdf, CreaturePtr beast, const std::string& plural_sid, const std::string& singular_sid, const std::string& id, const bool is_for_race) const;

    const std::string separator;
};

