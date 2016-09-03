#pragma once
#include "ICreatureRegeneration.hpp"
#include "IMessageManager.hpp"

class CreatureStatsIncrementer : public ICreatureRegeneration
{
  public:
    CreatureStatsIncrementer();
    CreatureStatsIncrementer(const uint new_minutes_interval);

    void tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed) override;

  protected:
    void increment_stat_if_necessary(std::pair<Statistic&, std::string>& stat_pair, IMessageManager& manager);

    int minutes_interval;
    static const int PCT_CHANCE_INCREMENT_STATISTIC;
};
