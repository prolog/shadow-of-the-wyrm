#include "TreeSpeciesFactory.hpp"

TreeSpecies TreeSpeciesFactory::create_tree_species(const TreeSpeciesID species_id)
{
  static_assert(TreeSpeciesID::TREE_SPECIES_LAST == TreeSpeciesID(31), "Unrecognized TREE_SPECIES_ID_LAST");

  TreeSpecies ts;

  ts.species_id = species_id;
  TileType tt = TileType::TILE_TYPE_UNDEFINED;

  switch (species_id)
  {
    case TreeSpeciesID::TREE_SPECIES_ASPEN:
    case TreeSpeciesID::TREE_SPECIES_MAPLE:
    case TreeSpeciesID::TREE_SPECIES_YEW:
    case TreeSpeciesID::TREE_SPECIES_OAK:
    case TreeSpeciesID::TREE_SPECIES_MOUNTAIN_ASH:
    case TreeSpeciesID::TREE_SPECIES_ASH:
    case TreeSpeciesID::TREE_SPECIES_BIRCH:
    case TreeSpeciesID::TREE_SPECIES_WALNUT:
      tt = TileType::TILE_TYPE_TREE;
      break;
    case TreeSpeciesID::TREE_SPECIES_APPLE:
    case TreeSpeciesID::TREE_SPECIES_CHERRY:
    case TreeSpeciesID::TREE_SPECIES_PEACH:
    case TreeSpeciesID::TREE_SPECIES_PLUM:
    case TreeSpeciesID::TREE_SPECIES_PEAR:
    case TreeSpeciesID::TREE_SPECIES_OLIVE:
      tt = TileType::TILE_TYPE_FRUIT_TREE;
      break;
    case TreeSpeciesID::TREE_SPECIES_CEDAR:
    case TreeSpeciesID::TREE_SPECIES_SPRUCE:
    case TreeSpeciesID::TREE_SPECIES_PINE:
      tt = TileType::TILE_TYPE_EVERGREEN_TREE;
      break;
    case TreeSpeciesID::TREE_SPECIES_WEED1:
    case TreeSpeciesID::TREE_SPECIES_WEED2:
    case TreeSpeciesID::TREE_SPECIES_WEED3:
    case TreeSpeciesID::TREE_SPECIES_WEED4:
    case TreeSpeciesID::TREE_SPECIES_WEED5:
    case TreeSpeciesID::TREE_SPECIES_WEED6:
    case TreeSpeciesID::TREE_SPECIES_WEED7:
    case TreeSpeciesID::TREE_SPECIES_WEED8:
    case TreeSpeciesID::TREE_SPECIES_WEED9:
    case TreeSpeciesID::TREE_SPECIES_WEED10:
    case TreeSpeciesID::TREE_SPECIES_WEED11:
    case TreeSpeciesID::TREE_SPECIES_WEED12:
      tt = TileType::TILE_TYPE_WEEDS;
      break;
    default:
      break;
  }

  ts.tile_type = tt;

  return ts;
}
