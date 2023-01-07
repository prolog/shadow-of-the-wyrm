#pragma once
#include <map>
#include <memory>
#include <string>
#include "common.hpp"
#include "ISerializable.hpp"
#include "tiles.hpp"
#include "ScriptDetails.hpp"

enum struct MapExitOutcome
{
  CAN_EXIT = 0,
  NO_EXIT = 1,
  EXIT_BLOCKED = 2
};

class MapExit : public ISerializable
{
  public:
    MapExit();
    ~MapExit();
    bool operator==(const MapExit& me) const;

    void set_map_id(const std::string& map_id);
    std::string get_map_id() const;

    void set_terrain_type(const TileType new_tile_type);
    TileType get_terrain_type() const;

    bool is_using_map_id() const;
    bool is_using_terrain_type() const;

    void set_coordinate(const Coordinate& c);
    Coordinate get_coordinate() const;
    bool has_coordinate() const;

    void set_property(const std::string& prop, const std::string& val);
    std::string get_property(const std::string& prop) const;
    bool has_property(const std::string& prop) const;
    std::map<std::string, std::string> get_properties() const;

    void clear_event_scripts();
    void set_event_scripts(const EventScriptsMap& esm);
    EventScriptsMap get_event_scripts() const;
    EventScriptsMap& get_event_scripts_ref();
    void add_event_script(const std::string& event_name, const ScriptDetails& sd);
    bool has_event_script(const std::string& event_name);
    ScriptDetails get_event_script(const std::string& event_name) const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string map_id;
    TileType terrain_type;
    Coordinate coord;
    std::map<std::string, std::string> properties;
    EventScriptsMap event_scripts;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using MapExitPtr = std::shared_ptr<MapExit>;
