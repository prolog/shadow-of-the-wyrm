#include "TileSafetyCondition.hpp"
#include "ItemProperties.hpp"

bool TileSafetyCondition::is_safe(CreaturePtr creature, TilePtr tile) const
{
	bool safe = is_tile_safe(creature, tile);

	if (!safe && tile != nullptr)
	{
		if (tile->get_unprotected_movement_is_death(creature))
		{
			safe = creature->has_item_with_property(ItemProperties::ITEM_PROPERTIES_NEXUS);
		}
	}

	return safe;
}