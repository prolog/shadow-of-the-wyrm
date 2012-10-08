#pragma once
#include <vector>
#include "ICreatureRegeneration.hpp"
#include "ITimeObserver.hpp"

class CreatureTimeObserver : public ITimeObserver
{
  public:
    CreatureTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);

    ITimeObserver* clone();

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);
    
  protected:
    void initialize_regeneration_helpers();
  
    std::vector<ICreatureRegenerationPtr> regen;

  private:
    ClassIdentifier internal_class_identifier() const;
};
