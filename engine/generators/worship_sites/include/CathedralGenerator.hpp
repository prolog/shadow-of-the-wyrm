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
    virtual void generate_pews(MapPtr map, const int pew_end_row, const int pew_end_col);
    virtual void generate_fountains(MapPtr map);
    virtual void generate_dais_and_altar(MapPtr map, const int start_row, const int start_col, const int dais_height, const int dais_width);
    virtual void generate_doors(MapPtr map);
    
    virtual void generate_back_rooms(MapPtr map, const int back_rooms_start_col);
    virtual void generate_priest_quarters(MapPtr map, const int room_start_col);
    virtual void generate_secondary_back_room(MapPtr map, const int room_start_col);
    
    int start_row;
    int start_col;
    int church_height;
    int church_width;
};
