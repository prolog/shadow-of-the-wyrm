#pragma once
#include "Generator.hpp"

class WildOrchardGenerator : public SL::Generator
{
  public:
    WildOrchardGenerator(const std::string& map_exit_id);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dimensions);

  protected:
    virtual void add_map_features(MapPtr map);
};
