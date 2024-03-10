#include "Music.hpp"
#include "Serialize.hpp"

using namespace std;

Music::Music()
{
}

Music::Music(const vector<Song>& songs)
{
	for (const auto& song : songs)
	{
		string id = song.get_id();
		TileType tile_type = song.get_tile_type();
		MapType map_type = song.get_map_type();
		string location = song.get_location();

		if (!id.empty())
		{
			id_locations[id] = location;
		}

		if (tile_type != TileType::TILE_TYPE_UNDEFINED)
		{
			tile_type_locations[tile_type] = location;
		}

		if (map_type != MapType::MAP_TYPE_NULL)
		{
			map_type_locations[map_type] = location;
		}
	}
}

bool Music::operator==(const Music& rhs) const
{
	bool eq = true;

	eq = (id_locations == rhs.id_locations);
	eq = eq && (tile_type_locations == rhs.tile_type_locations);
	eq = eq && (map_type_locations == rhs.map_type_locations);

	return eq;
}

string Music::get_song(const string& id) const
{
	string song;
	auto l_it = id_locations.find(id);

	if (l_it != id_locations.end())
	{
		song = l_it->second;
	}

	return song;
}

string Music::get_song(const TileType tile_type) const
{
	string song;
	auto l_it = tile_type_locations.find(tile_type);

	if (l_it != tile_type_locations.end())
	{
		song = l_it->second;
	}

	return song;
}

string Music::get_song(const MapType mt) const
{
	string song;
	auto l_it = map_type_locations.find(mt);

	if (l_it != map_type_locations.end())
	{
		song = l_it->second;
	}

	return song;
}

bool Music::serialize(ostream& stream) const
{
	Serialize::write_size_t(stream, id_locations.size());

	for (const auto& id_pair : id_locations)
	{
		Serialize::write_string(stream, id_pair.first);
		Serialize::write_string(stream, id_pair.second);
	}

	Serialize::write_size_t(stream, tile_type_locations.size());

	for (const auto tt_pair : tile_type_locations) 
	{
		Serialize::write_enum(stream, tt_pair.first);
		Serialize::write_string(stream, tt_pair.second);
	}

	Serialize::write_size_t(stream, map_type_locations.size());

	for (const auto& mt_pair : map_type_locations)
	{
		Serialize::write_enum(stream, mt_pair.first);
		Serialize::write_string(stream, mt_pair.second);
	}

	return true;
}

bool Music::deserialize(istream& stream)
{
	id_locations.clear();
	map_type_locations.clear();

	size_t id_l_s = 0;
	Serialize::read_size_t(stream, id_l_s);

	for (size_t id_idx = 0; id_idx < id_l_s; id_idx++)
	{
		string id;
		string location;

		Serialize::read_string(stream, id);
		Serialize::read_string(stream, location);

		id_locations[id] = location;
	}

	size_t tt_l_s = 0;
	Serialize::read_size_t(stream, tt_l_s);

	for (size_t tt_idx = 0; tt_idx < tt_l_s; tt_idx++)
	{
		TileType tile_type = TileType::TILE_TYPE_UNDEFINED;
		string location;

		Serialize::read_enum(stream, tile_type);
		Serialize::read_string(stream, location);

		tile_type_locations[tile_type] = location;
	}

	size_t mt_l_s = 0;
	Serialize::read_size_t(stream, mt_l_s);

	for (size_t mt_idx = 0; mt_idx < mt_l_s; mt_idx++)
	{
		MapType mt = MapType::MAP_TYPE_NULL;
		string location;

		Serialize::read_enum(stream, mt);
		Serialize::read_string(stream, location);

		map_type_locations[mt] = location;
	}

	return true;
}

ClassIdentifier Music::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_MUSIC;
}

#ifdef UNIT_TESTS
#include "unit_tests/Music_test.cpp"
#endif
