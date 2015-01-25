#pragma once
#include "Creature.hpp"

class StatisticsCalculator
{
  public:
    int calculate_current(CreaturePtr creature) const;

  protected:
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

