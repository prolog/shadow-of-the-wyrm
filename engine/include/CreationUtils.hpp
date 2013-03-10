#pragma once
#include "common.hpp"
#include "RarityTypes.hpp"

class CreationUtils
{
  public:
    static const uint MAX_UNSUCCESSFUL_CREATURE_ATTEMPTS;
    static const uint MAX_UNSUCCESSFUL_ITEM_ATTEMPTS;

    static uint random_maximum_creatures(const int map_height, const int map_width);
    static uint random_maximum_items(const int map_height, const int map_width);

    static Rarity generate_rarity();

  protected:
    CreationUtils();
    ~CreationUtils();
};
