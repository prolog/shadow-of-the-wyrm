#pragma once
#include "SkillProcessor.hpp"

class MusicSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;

  protected:
    ItemPtr get_musical_instrument(CreaturePtr creature);
    std::pair<std::string, std::string> get_instrument_performance_sids(ItemPtr item);
    bool is_vocal_performance(ItemPtr item);
    
    void perform(CreaturePtr creature, MapPtr map, ItemPtr instr, const std::pair<std::string, std::string>& performance_sids);
    void add_start_performance_message(CreaturePtr creature);
    void add_performance_details_message(CreaturePtr creature, const std::string& perf_sid);
    void add_not_pacifiable_message(CreaturePtr creature, CreaturePtr fov_creature);

    void pacify(CreaturePtr creature, CreaturePtr fov_creature);
    bool get_charms_creature(ItemPtr item, CreaturePtr fov_creature);

    // Attempt pacification, updating the hostile/pacified counts as required
    void attempt_pacification(ItemPtr instr, CreaturePtr creature, CreaturePtr fov_creature, int& num_hostile, int& num_pacified);

    void enrage(CreaturePtr creature, CreaturePtr fov_creature);
};


