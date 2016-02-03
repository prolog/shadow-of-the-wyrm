#pragma once
#include "Generator.hpp"

enum struct CastleType
{
  CASTLE_TYPE_MOTTE_AND_BAILEY = 0,
/*  CASTLE_TYPE_RECTANGULAR_KEEP = 1,
  CASTLE_TYPE_CIRCULAR_KEEP = 2,
  CASTLE_TYPE_CONCENTRIC = 3 */
  CASTLE_TYPE_LAST = 0 // Used for random type generation
};

class CastleGenerator : public SOTW::Generator
{
  public:
    CastleGenerator(const std::string& map_exit_id, const TileType base_tile, const CastleType castle_type = CastleType::CASTLE_TYPE_MOTTE_AND_BAILEY);

    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual bool get_permanence_default() const override;

    void generate_castle(MapPtr map);

    TileType base_tile_type;
    CastleType castle_type;
};

