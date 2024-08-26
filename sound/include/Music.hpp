#pragma once
#include <map>
#include <string>
#include <vector>
#include "ISerializable.hpp"
#include "Song.hpp"
#include "MapTypes.hpp"

class Music : public ISerializable
{
	public:
		Music();
		Music(const std::vector<Song>& songs);

		bool operator==(const Music& rhs) const;

		std::string get_event_song(const std::string& event, const ternary winner) const;
		std::string get_song(const std::string& id, const ternary winner) const;
		std::string get_song(const TileType tile_type, const ternary winner) const;
		std::string get_song(const MapType map_type, const ternary winner) const;

		virtual bool serialize(std::ostream& stream) const override;
		virtual bool deserialize(std::istream& stream) override;

	protected:
		template<typename C, typename K>
		std::string song_match(const C& collection, const K& key, const ternary winner)
		{
			return "";
		}

		std::map<std::pair<std::string, ternary>, std::string> event_locations;
		std::map<std::pair<std::string, ternary>, std::string> id_locations;
		std::map<std::pair<TileType, ternary>, std::string> tile_type_locations;
		std::map<std::pair<MapType, ternary>, std::string> map_type_locations;

	private:
		ClassIdentifier internal_class_identifier() const;
};