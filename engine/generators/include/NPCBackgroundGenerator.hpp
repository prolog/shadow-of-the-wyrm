#pragma once
#include "Creature.hpp"
#include <vector>

class NPCBackgroundGenerator
{
	public:
		NPCBackgroundGenerator();
		NPCBackgroundGenerator(const bool include_all);

		std::string generate_bestiary(CreaturePtr creature) const;

	protected:
		std::string generate_hair(CreaturePtr creature) const;
		std::string generate_eyes(CreaturePtr creature) const;
		std::string generate_handedness(CreaturePtr creature) const;
		std::string generate_parents(CreaturePtr creature) const;
		std::string generate_children(CreaturePtr creature) const;
		std::vector<std::string> generate_personality(CreaturePtr creature) const;
		std::string generate_former_job(CreaturePtr creature) const;
		std::string generate_negative_life_event(CreaturePtr creature) const;
		std::vector<std::string> generate_habits(CreaturePtr creature) const;
		std::string generate_travel(CreaturePtr creature) const;
		std::string generate_born(CreaturePtr creature) const;
		std::string generate_love(CreaturePtr creature) const;
		std::string generate_phobia(CreaturePtr creature) const;
		std::vector<std::string> generate_misc(CreaturePtr creature) const;

		std::string generate_bestiary_text(const std::vector<std::string>& fragments) const;

		bool include_all;
};
