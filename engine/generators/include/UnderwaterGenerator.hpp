#include "Generator.hpp"
#include "Map.hpp"

class UnderwaterGenerator : public SOTW::Generator
{
	public:
		UnderwaterGenerator(MapPtr above_water_map, const std::string& map_exit_id);

		virtual MapPtr generate(const Dimensions& dim) override;
		virtual MapType get_map_type() const override;

protected:
		void add_items(TilePtr tile, const TileType above_tile_type, const int generation_rate, const int rock_generation_rate);

		void init_underwater_item_ids();

		MapPtr above_water_map;
		std::vector<std::pair<std::string, int>> underwater_item_ids;
		
		static const int PCT_CHANCE_ROCKY_BOTTOM;
		static const int PCT_CHANCE_CORPSES;
		static const int PCT_CHANCE_SPRINGS_IVORY;
		static const int PCT_CHANCE_UNDERWATER_ITEMS;
		static const int PCT_CHANCE_UNDERWATER_ITEMS_LOWER;
		static const int PCT_CHANCE_UNDERWATER_ITEMS_UPPER;
		static const int PCT_CHANCE_ROCK_LOWER;
		static const int PCT_CHANCE_ROCK_UPPER;
};
