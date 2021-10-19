#pragma once
#include "SkillProcessor.hpp"

enum struct PacificationOutcome
{
  PACIFICATION_OUTCOME_SUCCESS = 0,
  PACIFICATION_OUTCOME_FAILURE = 1,
  PACIFICATION_OUTCOME_NOT_PACIFIABLE = 2
};

class MusicSkillProcessor : public SkillProcessor
{
  public:
    virtual ActionCostValue process(CreaturePtr creature, MapPtr map) override;
    virtual SkillProcessorPtr clone() override;

  protected:
    ItemPtr get_musical_instrument(CreaturePtr creature);
    std::pair<std::string, std::string> get_instrument_performance_sids(ItemPtr item);
    bool is_vocal_performance(ItemPtr item);
    
    void perform(CreaturePtr creature, MapPtr map, ItemPtr instr, const std::pair<std::string, std::string>& performance_sids);
    void add_start_performance_message(CreaturePtr creature);
    void add_performance_details_message(CreaturePtr creature, const std::string& perf_sid);
    void add_not_pacifiable_message(CreaturePtr creature, CreaturePtr fov_creature);

    void pacify(CreaturePtr creature, CreaturePtr fov_creature, const bool charms_creature);
    bool get_charms_creature(ItemPtr item, CreaturePtr fov_creature);

    // Attempt pacification, updating the hostile/pacified counts as required
    PacificationOutcome attempt_pacification(ItemPtr instr, CreaturePtr creature, CreaturePtr fov_creature, MapPtr current_map, int& num_hostile, int& num_pacified);

    void add_unimpressed_message(CreaturePtr creature, CreaturePtr fov_creature);
    void enrage(CreaturePtr creature, CreaturePtr fov_creature);

    void run_pacification_event(CreaturePtr creature, CreaturePtr fov_creature);
};


