#pragma once
#include "ChurchGenerator.hpp"

// A twisting temple in the shape of a serpent.  Built by the followers
// of Voros.
class SnakingTempleGenerator : public ChurchGenerator
{
  public:
    SnakingTempleGenerator(const std::string& new_deity_id, MapPtr new_base_map);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual void initialize_temple_values(const int rows, const int cols);
    virtual void generate_temple(MapPtr map);
    virtual void connect_buildings(MapPtr map);
    virtual void generate_L_hallway(MapPtr map, const int start_row, const int start_col, const int end_row, const int end_col);
    virtual void generate_temple_doors(MapPtr map);

    virtual void generate_room_of_worship(MapPtr map);
    virtual void generate_pews(MapPtr map);
    virtual void generate_dais(MapPtr map, const int dais_row, const int dais_col);
    virtual void generate_altar(MapPtr map, const int dais_row, const int dais_col);
    virtual void generate_fountains(MapPtr map);
    virtual void generate_statues(MapPtr map);
    
    virtual void generate_fire_pillars(MapPtr map);
    virtual void generate_fire_pillars_in_entrance(MapPtr map);
    virtual void generate_fire_pillars_in_hall_of_heroes(MapPtr map);
    virtual void generate_fire_pillars_in_room_of_worship(MapPtr map);
    
    virtual int get_temple_width_min(const int num_cols);
    virtual int get_temple_width_max(const int num_cols);
    
    virtual int get_temple_height_min(const int num_rows);
    virtual int get_temple_height_max(const int num_rows);
    
    // For easy refactoring, since all the various feature placement make very heavy use of these
    int temple_width;
    int temple_height;
    int temple_middle_width;
    int temple_middle_height;
    int temple_row_start;
    int temple_row_end;
    int temple_col_start;
    int temple_col_end;
    int head_height;
    int temple_middle_start_row;
    int temple_middle_end_row;
    int temple_middle_start_col;
    int temple_middle_end_col;
};
