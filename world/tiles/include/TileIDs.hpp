#pragma once
#include <string>

class TileCustomMapIDs
{
  public:
    static const std::string CUSTOM_MAP_ID_ISEN_DUN;
    static const std::string CUSTOM_MAP_ID_LAST_ISLAND_LAIR;
    static const std::string CUSTOM_MAP_ID_THE_BARROWS;
    static const std::string CUSTOM_MAP_ID_WINTERSEA_KEEP;

  protected:
    TileCustomMapIDs();
    ~TileCustomMapIDs();
};

enum TreeSpeciesID
{
  TREE_SPECIES_ASPEN,
  TREE_SPECIES_MAPLE,
  TREE_SPECIES_YEW,
  TREE_SPECIES_OAK,
  TREE_SPECIES_MOUNTAIN_ASH,
  TREE_SPECIES_ASH,
  TREE_SPECIES_BIRCH,
  TREE_SPECIES_CYPRESS,
  TREE_SPECIES_WALNUT,
};
