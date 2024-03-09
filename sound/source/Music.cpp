#include "Music.hpp"

using namespace std;

Music::Music(const vector<Song>& songs)
{
	for (const auto& song : songs)
	{
		string id = song.get_id();
		MapType map_type = song.get_map_type();
		string location = song.get_location();

		if (!id.empty())
		{
			id_locations[id] = location;
		}

		if (map_type != MapType::MAP_TYPE_NULL)
		{
			map_type_locations[map_type] = location;
		}
	}
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