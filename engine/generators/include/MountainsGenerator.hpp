#pragma once
#include "Generator.hpp"

class MountainsGenerator : public SOTW::Generator
{
  public:
    MountainsGenerator(const std::string& map_exit_id);
    virtual ~MountainsGenerator() = default;

    MapPtr generate(const Dimensions& dim) override;

  protected:
    void generate_stream(MapPtr result_map);
    void generate_cliffs(MapPtr result_map);
};
