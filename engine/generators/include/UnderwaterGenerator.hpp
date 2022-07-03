#include "Generator.hpp"
#include "Map.hpp"

class UnderwaterGenerator : public SOTW::Generator
{
	public:
		UnderwaterGenerator(MapPtr above_water_map, const std::string& map_exit_id);

		virtual MapPtr generate(const Dimensions& dim) override;

	protected:
		MapPtr above_water_map;
};
