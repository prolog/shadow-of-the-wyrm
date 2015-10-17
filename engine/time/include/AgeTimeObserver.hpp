#pragma once
#include "ITimeObserver.hpp"
#include "Map.hpp"

class AgeTimeObserver : public ITimeObserver
{
  public:
    AgeTimeObserver();
    
    void notify(const ulonglong minutes_elapsed) override;

    ITimeObserver* clone() override;

  protected:
    void process_creatures(MapPtr cur_map, std::map<std::string, CreaturePtr>& creature_map);

  private:
    ClassIdentifier internal_class_identifier() const override;
};
