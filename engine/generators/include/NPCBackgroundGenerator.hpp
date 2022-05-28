#pragma once
#include "Creature.hpp"

class NPCBackgroundGenerator
{
	public:
		std::string generate_bestiary(CreaturePtr creature) const;

	protected:
		std::string generate_hair(CreaturePtr creature) const;
		std::string generate_eyes(CreaturePtr creature) const;
		std::string generate_handedness(CreaturePtr creature) const;
};
