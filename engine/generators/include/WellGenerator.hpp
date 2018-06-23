#pragma once
#include "Generator.hpp"

class WellGenerator : public SOTW::Generator
{
  public:
    WellGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual bool get_permanence_default() const override;
    virtual MapType get_map_type() const override;

    virtual void create_open_section(MapPtr result_map, const Coordinate& up_staircase_coord, const Coordinate& open_start, const Coordinate& open_end);
    virtual void create_stream(MapPtr result_map, const Coordinate& open_start, const Coordinate& open_end);
};
