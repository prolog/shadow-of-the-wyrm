#include "CreatureCalculator.hpp"
#include "CreatureToHitCalculator.hpp"
#include "CreatureAdditionalDamageCalculator.hpp"
#include "EvadeCalculator.hpp"
#include "RaceManager.hpp"
#include "ClassManager.hpp"
#include "ResistancesCalculator.hpp"
#include "SoakCalculator.hpp"
#include "StatisticsCalculators.hpp"

CreatureCalculator::CreatureCalculator()
{
}

CreatureCalculator::~CreatureCalculator()
{
}

void CreatureCalculator::update_calculated_values(const CreaturePtr& c)
{
  if (c)
  {
    // Strength
    StrengthCalculator sc;
    Statistic str = c->get_strength();
    str.set_current(sc.calculate_current(c));
    c->set_strength(str);

    // Dexterity
    DexterityCalculator dc;
    Statistic dex = c->get_dexterity();
    dex.set_current(dc.calculate_current(c));
    c->set_dexterity(dex);

    // Agility
    AgilityCalculator ac;
    Statistic agi = c->get_agility();
    agi.set_current(ac.calculate_current(c));
    c->set_agility(agi);

    // Health
    HealthCalculator hc;
    Statistic hea = c->get_health();
    hea.set_current(hc.calculate_current(c));
    c->set_health(hea);

    // Intelligence
    IntelligenceCalculator ic;
    Statistic itl = c->get_intelligence();
    itl.set_current(ic.calculate_current(c));
    c->set_intelligence(itl);

    // Willpower
    WillpowerCalculator wc;
    Statistic wil = c->get_willpower();
    wil.set_current(wc.calculate_current(c));
    c->set_willpower(wil);

    // Charisma
    CharismaCalculator cc;
    Statistic cha = c->get_charisma();
    cha.set_current(cc.calculate_current(c));
    c->set_charisma(cha);
 
    // Evade
    int calc_evade = EvadeCalculator::calculate_evade(c);
    c->set_evade(calc_evade);

    // Soak
    int calc_soak = SoakCalculator::calculate_soak(c);
    c->set_soak(calc_soak);

    // To-Hit from additional sources
    CreatureToHitCalculator cthc;
    int calc_to_hit = cthc.calculate_to_hit(c);
    c->set_to_hit(calc_to_hit);

    // TODO: If additional damage is ever added to Modifier, update this.
    // Damage from additional sources
    CreatureAdditionalDamageCalculator cadc;
    int calc_addl_damage = cadc.calculate_additional_damage(c);
    c->set_addl_damage(calc_addl_damage);

    // TODO: If resistances are ever added to Modifier, update this.
    // Resistances
    RaceManager rm;
    ClassManager cm;
    ResistancesCalculator rc;
    Resistances resists = rc.calculate_resistances(c, rm.get_race(c->get_race_id()), cm.get_class(c->get_class_id()));
    c->set_resistances(resists);
  }
}
