#pragma once
#include "Creature.hpp"

class StatisticsCalculator
{
  public:
    virtual ~StatisticsCalculator() = default;

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
  public:
    virtual ~StrengthCalculator() = default;

  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class DexterityCalculator : public StatisticsCalculator
{
  public:
    virtual ~DexterityCalculator() = default;

  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class AgilityCalculator : public StatisticsCalculator
{
  public:
    virtual ~AgilityCalculator() = default;

  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class HealthCalculator : public StatisticsCalculator
{
  public:
    virtual ~HealthCalculator() = default;

  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class IntelligenceCalculator : public StatisticsCalculator
{
  public:
    virtual ~IntelligenceCalculator() = default;

  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class WillpowerCalculator : public StatisticsCalculator
{
  public:
    virtual ~WillpowerCalculator() = default;

  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class CharismaCalculator : public StatisticsCalculator
{
  public:
    virtual ~CharismaCalculator() = default;

  protected:
    virtual int get_base_statistic_value(CreaturePtr creature) const override;
    virtual int get_modifier_statistic_value(const Modifier& modifier) const override;
};

class SpeedCalculator : public StatisticsCalculator
{
  public:
    virtual ~SpeedCalculator() = default;

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