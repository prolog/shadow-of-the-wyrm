#include "PointsTransfer.hpp"

// Transfer up to amount points to the creature's HP/AP, without going over
// the maximum.  Return the amount transferred.
int PointsTransfer::transfer(CreaturePtr creature, const int amount, const PointsTransferType pt)
{
  int trans = 0;

  if (creature != nullptr)
  {
    Statistic stat = get_statistic(creature, pt);
    trans = std::min<int>(amount, (stat.get_base() - stat.get_current()));

    if (trans > 0)
    {
      stat.set_current(stat.get_current() + trans);
      set_statistic(creature, stat, pt);
    }
  }

  return trans;
}

// Get the points available for HP/AP transfer.
int PointsTransfer::get_points_for_transfer(CreaturePtr attacked_creature, const int amount, const PointsTransferType pt) const
{
  int trans = 0;

  if (attacked_creature != nullptr)
  {
    Statistic stat = get_statistic(attacked_creature, pt);
    int cur_val = stat.get_current();

    if (cur_val > amount)
    {
      trans = amount;
    }
    else
    {
      trans = std::max<int>(cur_val, 0);
    }
  }

  return trans;
}

bool PointsTransfer::set_statistic(CreaturePtr creature, const Statistic& stat, const PointsTransferType pt)
{
  bool set_stat = false;

  if (creature != nullptr)
  {
    if (pt == PointsTransferType::POINTS_TRANSFER_HP)
    {
      creature->set_hit_points(stat);
    }
    else
    {
      creature->set_arcana_points(stat);
    }

    set_stat = true;
  }

  return set_stat;
}

Statistic PointsTransfer::get_statistic(CreaturePtr creature, const PointsTransferType pt) const
{
  Statistic stat;

  if (creature != nullptr)
  {
    if (pt == PointsTransferType::POINTS_TRANSFER_HP)
    {
      stat = creature->get_hit_points();
    }
    else
    {
      stat = creature->get_arcana_points();
    }
  }

  return stat;
}

#ifdef UNIT_TESTS
#include "unit_tests/PointsTransfer_test.cpp"
#endif