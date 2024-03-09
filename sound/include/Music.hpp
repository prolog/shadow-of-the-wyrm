#pragma once
#include <map>
#include <string>
#include <vector>
#include "Song.hpp"
#include "MapTypes.hpp"

class Music
{
	public:
		Music(const std::vector<Song>& songs);

		std::string get_song(const std::string& id) const;
		std::string get_song(const MapType map_type) const;

	protected:
		std::map<std::string, std::string> id_locations;
		std::map<MapType, std::string> map_type_locations;
};