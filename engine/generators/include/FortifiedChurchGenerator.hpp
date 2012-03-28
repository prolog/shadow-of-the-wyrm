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
    virtual void generate_church(MapPtr map);
    virtual void generate_parapets(MapPtr map, const int church_height, const int church_width);
    virtual void create_parapet(MapPtr map, const int start_row, const int start_col, const int parapet_size); 
};
