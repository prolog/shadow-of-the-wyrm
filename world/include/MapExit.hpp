#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
#include "ISerializable.hpp"
#include "tiles.hpp"

class MapExit : public ISerializable
{
  public:
    MapExit();
    ~MapExit();

    void set_map_id(const std::string& map_id);
    std::string get_map_id() const;

    void set_terrain_type(const TileType new_tile_type);
    TileType get_terrain_type() const;

    bool is_using_map_id() const;
    bool is_using_terrain_type() const;

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    std::string map_id;
    TileType terrain_type;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<MapExit> MapExitPtr;
