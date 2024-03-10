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

		std::string get_song(const std::string& id) const;
		std::string get_song(const TileType tile_type) const;
		std::string get_song(const MapType map_type) const;

		virtual bool serialize(std::ostream& stream) const override;
		virtual bool deserialize(std::istream& stream) override;

	protected:
		std::map<std::string, std::string> id_locations;
		std::map<TileType, std::string> tile_type_locations;
		std::map<MapType, std::string> map_type_locations;

	private:
		ClassIdentifier internal_class_identifier() const;
};