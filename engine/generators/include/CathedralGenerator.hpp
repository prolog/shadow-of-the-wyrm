#pragma once
#include "ChurchGenerator.hpp"

// Great cathedrals are built by the followers of Celeste, who celebrate
// the creator of the stars and sky with opulent buildings on earth.
class CathedralGenerator : public ChurchGenerator
{
  public:
    CathedralGenerator(const std::string& new_deity_id, MapPtr base_map);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual void generate_cathedral(MapPtr map);
};
