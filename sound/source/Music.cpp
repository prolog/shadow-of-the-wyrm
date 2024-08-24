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
		ternary winner = song.get_winner();
		string event = song.get_event();
		string id = song.get_id();
		TileType tile_type = song.get_tile_type();
		MapType map_type = song.get_map_type();
		string location = song.get_location();

		if (!event.empty())
		{
			event_locations[{event, winner}] = location;
		}

		if (!id.empty())
		{
			id_locations[{id, winner}] = location;
		}

		if (tile_type != TileType::TILE_TYPE_UNDEFINED)
		{
			tile_type_locations[{tile_type, winner}] = location;
		}

		if (map_type != MapType::MAP_TYPE_NULL)
		{
			map_type_locations[{map_type, winner}] = location;
		}
	}
}

bool Music::operator==(const Music& rhs) const
{
	bool eq = true;

	eq = (event_locations == rhs.event_locations);
	eq = eq && (id_locations == rhs.id_locations);
	eq = eq && (tile_type_locations == rhs.tile_type_locations);
	eq = eq && (map_type_locations == rhs.map_type_locations);

	return eq;
}

string Music::get_event_song(const string& event, const ternary winner) const
{
	string song;

	// First, try an exact match.
	auto ev_it = event_locations.find({ event, winner });

	if (ev_it != event_locations.end())
	{
		song = ev_it->second;
	}
	else
	{
		// If exact match fails, look for a match based on any win condition.
		ev_it = event_locations.find({ event, ternary::TERNARY_UNDEFINED });

		if (ev_it != event_locations.end())
		{
			song = ev_it->second;
		}
	}

	return song;
}

string Music::get_song(const string& id, const ternary winner) const
{
	string song; 
	
	// First, try an exact match.
	auto id_it = id_locations.find({ id, winner });

	if (id_it != id_locations.end())
	{
		song = id_it->second;
	}
	else
	{
		// If exact match fails, look for a match based on any win condition.
		id_it = id_locations.find({ id, ternary::TERNARY_UNDEFINED });

		if (id_it != id_locations.end())
		{
			song = id_it->second;
		}
	}

	return song;
}

string Music::get_song(const TileType tile_type, const ternary winner) const
{
	string song;

	// First, try an exact match.
	auto tt_it = tile_type_locations.find({ tile_type, winner });

	if (tt_it != tile_type_locations.end())
	{
		song = tt_it->second;
	}
	else
	{
		// If exact match fails, look for a match based on any win condition.
		tt_it = tile_type_locations.find({ tile_type, ternary::TERNARY_UNDEFINED });

		if (tt_it != tile_type_locations.end())
		{
			song = tt_it->second;
		}
	}

	return song;
}

string Music::get_song(const MapType mt, const ternary winner) const
{
	string song;

	// First, try an exact match.
	auto mt_it = map_type_locations.find({ mt, winner });

	if (mt_it != map_type_locations.end())
	{
		song = mt_it->second;
	}
	else
	{
		// If exact match fails, look for a match based on any win condition.
		mt_it = map_type_locations.find({ mt, ternary::TERNARY_UNDEFINED });

		if (mt_it != map_type_locations.end())
		{
			song = mt_it->second;
		}
	}

	return song;
}

bool Music::serialize(ostream& stream) const
{
	Serialize::write_size_t(stream, event_locations.size());

	for (const auto& event_pair : event_locations)
	{
		Serialize::write_string(stream, event_pair.first.first);
		Serialize::write_enum(stream, event_pair.first.second);
		Serialize::write_string(stream, event_pair.second);
	}

	Serialize::write_size_t(stream, id_locations.size());

	for (const auto& id_pair : id_locations)
	{
		Serialize::write_string(stream, id_pair.first.first);
		Serialize::write_enum(stream, id_pair.first.second);
		Serialize::write_string(stream, id_pair.second);
	}

	Serialize::write_size_t(stream, tile_type_locations.size());

	for (const auto tt_pair : tile_type_locations) 
	{
		Serialize::write_enum(stream, tt_pair.first.first);
		Serialize::write_enum(stream, tt_pair.first.second);
		Serialize::write_string(stream, tt_pair.second);
	}

	Serialize::write_size_t(stream, map_type_locations.size());

	for (const auto& mt_pair : map_type_locations)
	{
		Serialize::write_enum(stream, mt_pair.first.first);
		Serialize::write_enum(stream, mt_pair.first.second);
		Serialize::write_string(stream, mt_pair.second);
	}

	return true;
}

bool Music::deserialize(istream& stream)
{
	event_locations.clear();
	id_locations.clear();
	map_type_locations.clear();

	size_t ev_l_s = 0;
	Serialize::read_size_t(stream, ev_l_s);

	for (size_t ev_idx = 0; ev_idx < ev_l_s; ev_idx++)
	{
		string event;
		ternary winner;
		string location;

		Serialize::read_string(stream, event);
		Serialize::read_enum(stream, winner);
		Serialize::read_string(stream, location);

		event_locations[{event, winner}] = location;
	}

	size_t id_l_s = 0;
	Serialize::read_size_t(stream, id_l_s);

	for (size_t id_idx = 0; id_idx < id_l_s; id_idx++)
	{
		string id;
		ternary winner;
		string location;

		Serialize::read_string(stream, id);
		Serialize::read_enum(stream, winner);
		Serialize::read_string(stream, location);

		id_locations[{id, winner}] = location;
	}

	size_t tt_l_s = 0;
	Serialize::read_size_t(stream, tt_l_s);

	for (size_t tt_idx = 0; tt_idx < tt_l_s; tt_idx++)
	{
		TileType tile_type = TileType::TILE_TYPE_UNDEFINED;
		ternary winner;
		string location;

		Serialize::read_enum(stream, tile_type);
		Serialize::read_enum(stream, winner);
		Serialize::read_string(stream, location);

		tile_type_locations[{tile_type, winner}] = location;
	}

	size_t mt_l_s = 0;
	Serialize::read_size_t(stream, mt_l_s);

	for (size_t mt_idx = 0; mt_idx < mt_l_s; mt_idx++)
	{
		MapType mt = MapType::MAP_TYPE_NULL;
		ternary winner;
		string location;

		Serialize::read_enum(stream, mt);
		Serialize::read_enum(stream, winner);
		Serialize::read_string(stream, location);

		map_type_locations[{mt, winner}] = location;
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
