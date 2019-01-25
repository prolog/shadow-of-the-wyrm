#pragma once
#include "Creature.hpp"

class StatisticsCalculator
{
  public:
    int calculate_current(CreaturePtr creature) const;

  protected:
    virtual int get_equipment_value(CreaturePtr creature) const;
    virtual float get_burden_multiplier(CreaturePtr creature) const;
    virtual int get_value_multiplier() const;
    virtual int get_base_statistic_value(CreaturePtr creature) const = 0;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const = 0;
    int get_modifier_value(CreaturePtr creature) const;
};

class StrengthCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class DexterityCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class AgilityCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class HealthCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class IntelligenceCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class WillpowerCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class CharismaCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class SpeedCalculator : public StatisticsCalculator
{
  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
    virtual int get_value_multiplier() const override;
    virtual int get_equipment_value(CreaturePtr creature) const override;
    virtual float get_burden_multiplier(CreaturePtr creature) const override;

    const static float BURDENED_SPEED_MULTIPLIER;
    const static float STRAINED_SPEED_MULTIPLIER;
    const static float OVERBURDENED_SPEED_MULTIPLIER;
};