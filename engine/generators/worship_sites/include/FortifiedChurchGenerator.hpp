#pragma once
#include "ChurchGenerator.hpp"

// A fortified church is used by the followers of the Warlord, Aurelion.
class FortifiedChurchGenerator : public ChurchGenerator
{
  public:
    FortifiedChurchGenerator(const std::string& deity_name, MapPtr base_map);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual void initialize_dimensions(MapPtr map);
    virtual void generate_church(MapPtr map);
    virtual void generate_parapets(MapPtr map);
    virtual void create_parapet(MapPtr map, const int start_row, const int start_col, const int parapet_size);

    // Church features
    virtual void generate_features(MapPtr map);
    virtual void generate_altar(MapPtr map);
    virtual void generate_statues(MapPtr map);
    virtual void generate_doors(MapPtr map);
    
    int start_row;
    int start_col;
    int church_height;
    int church_width;
    int altar_row;
    int altar_col;
};
