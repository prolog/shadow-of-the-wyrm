#pragma once
#include "Creature.hpp"

enum struct PointsTransferType
{
  POINTS_TRANSFER_HP = 0,
  POINTS_TRANSFER_AP = 1
};

// Encapsulates transferring either HP or AP from one creature to another.
class PointsTransfer
{
  public:
    // If a creature has 6 HP, and the damage dealt was 30, the number of
    // points available for transfer is 6, not 30.
    int get_points_for_transfer(CreaturePtr attacked_creature, const int amount, const PointsTransferType pt) const;

    // Attempts to transfer the given amount of HP/AP to the creature, with 
    // the constaint that HP/AP cannot go over the maximum.  Returns the
    // amount actually transferred.
    int transfer(CreaturePtr creature, const int amount, const PointsTransferType pt);

  protected:
    bool set_statistic(CreaturePtr creature, const Statistic& stat, const PointsTransferType pt);
    Statistic get_statistic(CreaturePtr creature, const PointsTransferType pt) const;
};

