#pragma once
#include "DefaultTileConfiguration.hpp"

// Map of season to probability/generation details:
//
// - pair<int, int> - the x in y chance that the item with the given string
//   ID is generated.
// - string: the item ID.
typedef std::map<Season, std::vector<std::pair<std::pair<int, int>, std::string>>> AdditionalFloraMap;

class FieldTileConfiguration : public DefaultTileConfiguration
{
  public:
    FieldTileConfiguration();

    virtual void configure(TilePtr tile, const Season season) const override;

  protected:
    virtual void initialize_additional_flora_map();

    AdditionalFloraMap flora_map;
};

