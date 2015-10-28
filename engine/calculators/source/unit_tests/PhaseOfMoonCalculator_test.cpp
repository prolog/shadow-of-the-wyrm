#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_PhaseOfMoonCalculator, calculate_phase)
{
  PhaseOfMoonCalculator pomc;
  double seconds = 12.0;

  EXPECT_EQ(PhaseOfMoonType::PHASE_OF_MOON_NEW, pomc.calculate_phase_of_moon(seconds));

  seconds = 60*60*24 + 10000;

  EXPECT_EQ(PhaseOfMoonType::PHASE_OF_MOON_WAXING, pomc.calculate_phase_of_moon(seconds));

  seconds = 60*60*24*14 + 10000;

  EXPECT_EQ(PhaseOfMoonType::PHASE_OF_MOON_FULL, pomc.calculate_phase_of_moon(seconds));

  seconds = 60*60*24*18 + 20000;

  EXPECT_EQ(PhaseOfMoonType::PHASE_OF_MOON_WANING, pomc.calculate_phase_of_moon(seconds));
}