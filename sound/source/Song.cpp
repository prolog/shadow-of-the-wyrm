#include "Song.hpp"

using namespace std;

Song::Song()
{
}

Song::Song(const string& new_id, const MapType new_map_type, const string& new_location)
: id(new_id), map_type(new_map_type), location(new_location)
{
}

void Song::set_id(const string& new_id)
{
	id = new_id;
}

string Song::get_id() const
{
	return id;
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
