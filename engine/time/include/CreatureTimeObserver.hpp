#pragma once
#include <vector>
#include "ICreatureRegeneration.hpp"
#include "ITimeObserver.hpp"

class CreatureTimeObserver : public ITimeObserver
{
  public:
    CreatureTimeObserver();

    CreatureTimeObserver(const CreatureTimeObserver&) = delete;
    CreatureTimeObserver& operator=(const CreatureTimeObserver&) = delete;

    void notify(const ulonglong minutes_elapsed) override;

    std::unique_ptr<ITimeObserver> clone() override;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    
  protected:
    void initialize_regeneration_helpers();
  
    std::vector<ICreatureRegenerationPtr> regen;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
