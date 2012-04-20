#pragma once
#include "ChurchGenerator.hpp"

// Grand Temples are built by the follows of Vedere.  They are second
// only to the cathedrals of Celeste in terms of their splendor.
class GrandTempleGenerator : public ChurchGenerator
{
  public:
    GrandTempleGenerator(const std::string& new_deity_id, MapPtr new_base_map);
    
    virtual MapPtr generate(const Dimensions& d);
    virtual MapPtr generate();

  protected:
    void generate_temple(MapPtr map);
    void generate_temple_gardens(MapPtr map);
    void generate_temple_features(MapPtr map);
    void generate_temple_doors(MapPtr map);
    void generate_fountains(MapPtr map);
    void generate_altar(MapPtr map);
    
    void initialize_dimensions(MapPtr map);
    
    int temple_width;
    int temple_height;
    int temple_start_row;
    int temple_start_col;
    int centre_row;
    int centre_col;
};
