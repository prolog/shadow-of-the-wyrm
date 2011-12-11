#pragma once
#include <string>
class Creature;
class DisplayStatistics;

class CreatureTranslator
{
  public:
    static DisplayStatistics create_display_statistics(const CreaturePtr& creature);

  protected:
    CreatureTranslator();

    static std::string get_display_name(const CreaturePtr& c);

    static std::string get_display_strength(const CreaturePtr& c);
    static std::string get_display_dexterity(const CreaturePtr& c);
    static std::string get_display_agility(const CreaturePtr& c);
    static std::string get_display_health(const CreaturePtr& c);
    static std::string get_display_intelligence(const CreaturePtr& c);
    static std::string get_display_willpower(const CreaturePtr& c);
    static std::string get_display_charisma(const CreaturePtr& c);
};
