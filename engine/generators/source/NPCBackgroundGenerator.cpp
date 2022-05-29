#include <sstream>
#include "ColourTextKeys.hpp"
#include "Conversion.hpp"
#include "NPCBackgroundGenerator.hpp"
#include "NPCBackgroundTextKeys.hpp"
#include "RNG.hpp"
#include "TextMessages.hpp"

using namespace std;

NPCBackgroundGenerator::NPCBackgroundGenerator()
: include_all(true)
{
}

NPCBackgroundGenerator::NPCBackgroundGenerator(const bool new_include_all)
: include_all(new_include_all)
{
}

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

		string parents = generate_parents(creature);

		if (!parents.empty())
		{
			fragments.push_back(parents);
		}

		string children = generate_children(creature);

		if (!children.empty())
		{
			fragments.push_back(children);
		}

		vector<string> personality = generate_personality(creature);

		if (!personality.empty())
		{
			std::copy(personality.begin(), personality.end(), std::back_inserter(fragments));
		}

		string former_job = generate_former_job(creature);

		if (!former_job.empty())
		{
			fragments.push_back(former_job);
		}

		string negative_life_event = generate_negative_life_event(creature);

		if (!negative_life_event.empty())
		{
			fragments.push_back(negative_life_event);
		}

		vector<string> habits = generate_habits(creature);
		
		if (!habits.empty())
		{
			std::copy(habits.begin(), habits.end(), std::back_inserter(fragments));
		}

		ss << generate_bestiary_text(fragments);
	}

	return ss.str();
}

string NPCBackgroundGenerator::generate_hair(CreaturePtr creature) const
{
	ostringstream hair;

	if (creature != nullptr && (include_all || RNG::percent_chance(65)))
	{
		HairColour hair_colour = creature->get_hair_colour();
		if (hair_colour != HairColour::HAIR_NA)
		{
			string hair_sid = ColourTextKeys::get_colour_sid_from_hair_colour(hair_colour);
			hair << TextMessages::get_and_replace(NPCBackgroundTextKeys::FRAGMENT_HAIR, { StringTable::get(hair_sid) });
		}
	}

	return hair.str();
}

string NPCBackgroundGenerator::generate_eyes(CreaturePtr creature) const
{
	ostringstream eyes;

	if (creature && (include_all || RNG::percent_chance(65)))
	{
		eyes << TextMessages::get_and_replace(NPCBackgroundTextKeys::FRAGMENT_EYES, { StringTable::get(ColourTextKeys::get_colour_sid_from_eye_colour(creature->get_eye_colour())) });
	}

	return eyes.str();
}

string NPCBackgroundGenerator::generate_handedness(CreaturePtr creature) const
{
	ostringstream handed;

	if (creature != nullptr)
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

string NPCBackgroundGenerator::generate_parents(CreaturePtr creature) const
{
	ostringstream parents;

	if (creature && (include_all || RNG::percent_chance(75)))
	{
		vector<string> parent_details = String::create_string_vector_from_csv_string(StringTable::get(NPCBackgroundTextKeys::FRAGMENT_PARENTS));

		if (!parent_details.empty())
		{
			parents << parent_details.at(RNG::range(0, parent_details.size() - 1));
		}
	}

	return parents.str();
}

string NPCBackgroundGenerator::generate_children(CreaturePtr creature) const
{
	ostringstream children;

	if (creature != nullptr && (include_all || RNG::percent_chance(65)))
	{
		vector<string> children_details = String::create_string_vector_from_csv_string(StringTable::get(NPCBackgroundTextKeys::FRAGMENT_CHILDREN));

		if (!children_details.empty())
		{
			children << children_details.at(RNG::range(0, children_details.size() - 1));
		}
	}

	return children.str();
}

vector<string> NPCBackgroundGenerator::generate_personality(CreaturePtr creature) const
{
	vector<string> traits;

	if (creature)
	{
		vector<string> pers_details = String::create_string_vector_from_csv_string(StringTable::get(NPCBackgroundTextKeys::FRAGMENT_PERSONALITY));
		std::random_shuffle(pers_details.begin(), pers_details.end());

		int num_personality_traits = 0;

		if (include_all)
		{
			num_personality_traits = 3;
		}
		else
		{
			num_personality_traits = RNG::range(0, 3);
		}

		int cnt = 0;

		while (cnt != num_personality_traits && !pers_details.empty())
		{
			traits.push_back(StringTable::get(pers_details.back()));
			pers_details.pop_back();
			cnt++;
		}
	}

	return traits;
}

string NPCBackgroundGenerator::generate_former_job(CreaturePtr creature) const
{
	ostringstream ss;

	if (creature && (include_all || RNG::percent_chance(65)))
	{		
		vector<string> job_container = String::create_string_vector_from_csv_string(StringTable::get(NPCBackgroundTextKeys::FRAGMENT_FORMER_JOBS));

		if (!job_container.empty())
		{
			string job_c = job_container.at(RNG::range(0, job_container.size() - 1));
			vector<string> job_details = String::create_string_vector_from_csv_string(StringTable::get(NPCBackgroundTextKeys::FORMER_JOBS));
			std::random_shuffle(job_details.begin(), job_details.end());

			bool more_jobs = true;
			string former_job;

			while (!job_details.empty())
			{
				former_job = former_job + job_details.back();
				job_details.pop_back();

				if (RNG::percent_chance(20) && !job_details.empty())
				{
					former_job = former_job + ", ";
				}
				else
				{
					break;
				}
			}

			ss << TextMessages::get_and_replace(job_c, { former_job });
		}
	}

	return ss.str();
}

string NPCBackgroundGenerator::generate_negative_life_event(CreaturePtr creature) const
{
	ostringstream ss;

	if (creature != nullptr && (include_all || RNG::percent_chance(35)))
	{
		vector<string> neg_events = String::create_string_vector_from_csv_string(StringTable::get(NPCBackgroundTextKeys::FRAGMENT_NEGATIVE_LIFE_EVENTS));

		if (!neg_events.empty())
		{
			ss << neg_events.at(RNG::range(0, neg_events.size() - 1));
		}
	}

	return ss.str();
}

vector<string> NPCBackgroundGenerator::generate_habits(CreaturePtr creature) const
{
	vector<string> habits;

	if (creature != nullptr && (include_all || RNG::percent_chance(65)))
	{
		vector<string> habit_list = String::create_string_vector_from_csv_string(StringTable::get(NPCBackgroundTextKeys::HABITS));
		std::random_shuffle(habit_list.begin(), habit_list.end());

		int num_habits = 0;

		if (include_all)
		{
			num_habits = 3;
		}
		else
		{
			num_habits = RNG::range(0, 3);
		}

		int cnt = 0;

		while (cnt < num_habits && !habit_list.empty())
		{
			habits.push_back(habit_list.back());
			habit_list.pop_back();
			cnt++;
		}
	}

	return habits;
}

string NPCBackgroundGenerator::generate_bestiary_text(const vector<string>& frag) const
{
	ostringstream ss;
	vector<string> fragments = frag;

	std::random_shuffle(fragments.begin(), fragments.end());
	bool full_stop = true;

	for (size_t i = 0; i < fragments.size(); i++)
	{
		string f = fragments.at(i);

		if (!f.empty())
		{
			string fr = f;
			fr[0] = std::tolower(fr[0]);

			if (full_stop)
			{
				fr[0] = std::toupper(fr[0]);
			}

			ss << fr;

			// Last item always uses a period.  Otherwise, it'll usually use a period
			// but may use a semi-colon or comma for variation.
			if ((i == fragments.size() - 1) || RNG::percent_chance(85))
			{
				full_stop = true;
				ss << ". ";
			}
			else
			{
				full_stop = false;

				if (RNG::percent_chance(70) || fr.find(":") != string::npos)
				{
					ss << "; ";
				}
				else
				{
					ss << ", ";
				}
			}
		}
	}

	return ss.str();
}
