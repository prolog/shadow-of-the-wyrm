#pragma once
#include "Generator.hpp"

class KeepGenerator : public SOTW::Generator
{
  public:
    KeepGenerator(const std::string& map_exit_id, const int chance_decay = 0);
    KeepGenerator(MapPtr new_base_map, const int chance_decay = 0);
    virtual ~KeepGenerator() = default;

    virtual MapPtr generate(const Dimensions& dim) override;
    virtual MapPtr generate() override;

  protected:
    virtual bool get_permanence_default() const override;

    virtual void create_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    virtual void populate_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    virtual void create_entrance(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    
    MapPtr base_map;
    const int PCT_CHANCE_DECAY;
};
