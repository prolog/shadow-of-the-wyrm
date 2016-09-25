#include "gtest/gtest.h"

TEST(SW_World_Combat_PointsTransfer, transfer)
{
  PointsTransfer pt;

  // Case 1: Null creature
  EXPECT_EQ(0, pt.transfer(nullptr, 50, PointsTransferType::POINTS_TRANSFER_HP));
  EXPECT_EQ(0, pt.transfer(nullptr, 25, PointsTransferType::POINTS_TRANSFER_AP));

  // Case 2: full HP/AP
  CreaturePtr creature = std::make_shared<Creature>();
  Statistic hp(60);
  Statistic ap(60);

  creature->set_hit_points(hp);
  creature->set_arcana_points(ap);

  EXPECT_EQ(0, pt.transfer(creature, 50, PointsTransferType::POINTS_TRANSFER_HP));
  EXPECT_EQ(0, pt.transfer(creature, 25, PointsTransferType::POINTS_TRANSFER_AP));

  // Case 3: Neither HP nor AP full, but full transfer amount not reached.
  hp.set_current(40);
  ap.set_current(50);
  creature->set_hit_points(hp);
  creature->set_arcana_points(ap);

  EXPECT_EQ(20, pt.transfer(creature, 50, PointsTransferType::POINTS_TRANSFER_HP));
  EXPECT_EQ(60, creature->get_hit_points().get_current());
  EXPECT_EQ(10, pt.transfer(creature, 25, PointsTransferType::POINTS_TRANSFER_AP));
  EXPECT_EQ(60, creature->get_arcana_points().get_current());

  // Case 4: Full transfer amount reached.
  hp.set_current(5);
  ap.set_current(5);
  creature->set_hit_points(hp);
  creature->set_arcana_points(ap);

  EXPECT_EQ(50, pt.transfer(creature, 50, PointsTransferType::POINTS_TRANSFER_HP));
  EXPECT_EQ(55, creature->get_hit_points().get_current());
  EXPECT_EQ(25, pt.transfer(creature, 25, PointsTransferType::POINTS_TRANSFER_AP));
  EXPECT_EQ(30, creature->get_arcana_points().get_current());
}

TEST(SW_Engine_Combat_PointsTransfer, get_transfer_points)
{
  PointsTransfer pt;
  CreaturePtr creature = std::make_shared<Creature>();
  Statistic hp(30);
  Statistic ap(30);

  creature->set_hit_points(hp);
  creature->set_arcana_points(ap);

  EXPECT_EQ(12, pt.get_points_for_transfer(creature, 12, PointsTransferType::POINTS_TRANSFER_HP));
  EXPECT_EQ(30, pt.get_points_for_transfer(creature, 32, PointsTransferType::POINTS_TRANSFER_HP));
  EXPECT_EQ(14, pt.get_points_for_transfer(creature, 14, PointsTransferType::POINTS_TRANSFER_AP));
  EXPECT_EQ(30, pt.get_points_for_transfer(creature, 87, PointsTransferType::POINTS_TRANSFER_AP));
}