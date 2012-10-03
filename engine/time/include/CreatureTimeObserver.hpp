#pragma once
#include <vector>
#include "ICreatureRegeneration.hpp"
#include "ITimeObserver.hpp"

class CreatureTimeObserver : public ITimeObserver
{
  public:
    CreatureTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);
    
  protected:
    void initialize_regeneration_helpers();
  
    std::vector<ICreatureRegenerationPtr> regen;
};
