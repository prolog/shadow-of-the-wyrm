#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_PhaseOfMoonCalculator, calculate_phase)
{
  PhaseOfMoonCalculator pomc;

  vector<PhaseOfMoonType> phase_v = {PhaseOfMoonType::PHASE_OF_MOON_NEW, 
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WAXING,
                                     PhaseOfMoonType::PHASE_OF_MOON_FULL,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING,
                                     PhaseOfMoonType::PHASE_OF_MOON_WANING};

  for (size_t i = 0; i < phase_v.size(); i++)
  {
    EXPECT_EQ(phase_v.at(i), pomc.calculate_phase_of_moon(60*60*24*i));
  }
}