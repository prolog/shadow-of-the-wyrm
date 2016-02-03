#pragma once
#include "Generator.hpp"

class WildOrchardGenerator : public SOTW::Generator
{
  public:
    WildOrchardGenerator(const std::string& map_exit_id);

    virtual MapPtr generate() override;
    virtual MapPtr generate(const Dimensions& dimensions) override;

  protected:
    virtual void add_map_features(MapPtr map);
};
