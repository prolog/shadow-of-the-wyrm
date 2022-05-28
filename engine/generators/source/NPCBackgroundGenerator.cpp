#include <sstream>
#include <vector>
#include "ColourTextKeys.hpp"
#include "Conversion.hpp"
#include "NPCBackgroundGenerator.hpp"
#include "NPCBackgroundTextKeys.hpp"
#include "RNG.hpp"
#include "TextMessages.hpp"

using namespace std;

string NPCBackgroundGenerator::generate_bestiary(CreaturePtr creature) const
{
	ostringstream ss;

	if (creature != nullptr)
	{
		vector<string> fragments;

		string hair = generate_hair(creature);

		if (!hair.empty())
		{
			fragments.push_back(hair);
		}

		string eyes = generate_eyes(creature);

		if (!eyes.empty())
		{
			fragments.push_back(eyes);
		}

		string handedness = generate_handedness(creature);

		if (!handedness.empty())
		{
			fragments.push_back(handedness);
		}

		std::random_shuffle(fragments.begin(), fragments.end());
		bool full_stop = true;

		for (const auto& f : fragments)
		{
			if (!f.empty())
			{
				string fr = f;

				if (full_stop)
				{
					fr[0] = std::toupper(fr[0]);
				}

				ss << fr;
				
				if (RNG::percent_chance(85))
				{
					full_stop = true;
					ss << ". ";
				}
				else
				{
					full_stop = false;
					ss << RNG::percent_chance(65) ? "; " : ", ";
				}
			}
		}
	}

	return ss.str();
}

string NPCBackgroundGenerator::generate_hair(CreaturePtr creature) const
{
	ostringstream hair;

	if (creature != nullptr && RNG::percent_chance(50))
	{
		hair << TextMessages::get_and_replace(NPCBackgroundTextKeys::FRAGMENT_HAIR, { StringTable::get(ColourTextKeys::get_colour_sid_from_hair_colour(creature->get_hair_colour())) });
	}

	return hair.str();
}

string NPCBackgroundGenerator::generate_eyes(CreaturePtr creature) const
{
	ostringstream eyes;

	if (creature && RNG::percent_chance(50))
	{
		eyes << TextMessages::get_and_replace(NPCBackgroundTextKeys::FRAGMENT_EYES, { StringTable::get(ColourTextKeys::get_colour_sid_from_eye_colour(creature->get_eye_colour())) });
	}

	return eyes.str();
}

string NPCBackgroundGenerator::generate_handedness(CreaturePtr creature) const
{
	ostringstream handed;

	if (creature != nullptr && RNG::percent_chance(75))
	{
		Handedness handedness = creature->get_handedness();

		if (handedness == Handedness::LEFT_HANDED)
		{
			string handed_text = StringTable::get(RNG::percent_chance(50) ? NPCBackgroundTextKeys::LEFTY : NPCBackgroundTextKeys::SOUTHPAW);
			handed << handed_text;
		}
	}

	return handed.str();
}
