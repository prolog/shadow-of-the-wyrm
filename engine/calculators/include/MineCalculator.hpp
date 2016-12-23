#pragma once

class MineCalculator
{
  public:
    int calculate_pct_chance_magici_shards(const int danger_level) const;

  protected:
    static const int BASE_CHANCE_MAGICI_SHARDS;
};

