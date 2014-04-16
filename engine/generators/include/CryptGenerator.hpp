#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class CryptGenerator : public SL::Generator
{
  public:
    CryptGenerator(const std::string& new_map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual bool get_permanence_default() const override;

    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col);

    TileGenerator tg;
};
