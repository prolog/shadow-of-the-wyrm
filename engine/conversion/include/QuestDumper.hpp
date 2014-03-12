#pragma once
#include "Creature.hpp"
#include "StringConverter.hpp"
#include "Quests.hpp"

class QuestDumper : public StringConverter
{
  public:
    QuestDumper(CreaturePtr new_creature, const uint new_max_cols);
  
    std::string str() const override;

  protected:
    std::string get_quests() const;
    void dump_quest(std::ostream& stream, const Quest& quest) const;

    CreaturePtr creature;
    uint num_cols;
};
