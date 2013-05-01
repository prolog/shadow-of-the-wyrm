#pragma once
#include <boost/shared_ptr.hpp>
#include "Calendar.hpp"
#include "ISerializable.hpp"
#include "Map.hpp"

class MapRegistry;

class World : public ISerializable
{
  public:
    World();
    World(MapPtr new_world_map);
    ~World();
    bool operator==(const World& world) const;

    void set_world(MapPtr new_world_map);
    MapPtr get_world(const MapRegistry& map_registry) const;
    
    Calendar& get_calendar();

    bool serialize(std::ostream& stream);
    bool deserialize(std::istream& stream);

  protected:
    std::string world_map_id;
    Calendar calendar;

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<World> WorldPtr;
