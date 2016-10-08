#pragma once
#include "StringConverter.hpp"
#include "GenerationValues.hpp"
#include "Item.hpp"

class ArtifactDumper : public StringConverter
{
  public:
    ArtifactDumper(const ItemMap& new_item_map, const GenerationValuesMap& new_igv_map, const uint new_num_cols);

    std::string str() const override;

  protected:
    std::string get_artifacts() const;

    ItemMap item_map;
    GenerationValuesMap igv_map;
    uint num_cols;
};
