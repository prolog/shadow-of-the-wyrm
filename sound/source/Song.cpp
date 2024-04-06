#include "Song.hpp"

using namespace std;

Song::Song() : tile_type(TileType::TILE_TYPE_UNDEFINED), map_type(MapType::MAP_TYPE_NULL)
{
}

Song::Song(const string& new_event, const string& new_id, const TileType new_tile_type, const MapType new_map_type, const string& new_location)
: event(new_event), id(new_id), tile_type(new_tile_type), map_type(new_map_type), location(new_location)
{
}

void Song::set_event(const string& new_event)
{
	event = new_event;
}

string Song::get_event() const
{
	return event;
}

void Song::set_id(const string& new_id)
{
	id = new_id;
}

string Song::get_id() const
{
	return id;
}

void Song::set_tile_type(const TileType new_tile_type)
{
	tile_type = new_tile_type;
}

TileType Song::get_tile_type() const
{
	return tile_type;
}

void Song::set_map_type(const MapType new_map_type)
{
	map_type = new_map_type;
}

MapType Song::get_map_type() const
{
	return map_type;
}

void Song::set_location(const string& new_location)
{
	location = new_location;
}

string Song::get_location() const
{
	return location;
}
