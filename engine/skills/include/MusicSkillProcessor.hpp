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
    void add_performance_details_message(CreaturePtr creature, const std::string& perf_sid); 

    void pacify(CreaturePtr creature, CreaturePtr fov_creature);
    void enrage(CreaturePtr creature, CreaturePtr fov_creature);
};


