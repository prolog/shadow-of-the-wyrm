#include "Deity.hpp"
#include "Serialize.hpp"

using namespace std;

Deity::Deity()
: alignment_range(AlignmentRange::ALIGNMENT_RANGE_NEUTRAL), pct_chance_class_crowning(0), worship_site_type(WorshipSiteType::WORSHIP_SITE_CATHEDRAL), user_playable(false)
{
}

bool Deity::operator==(const Deity& d) const
{
  bool result = true;

  result = result && id == d.id;
  result = result && name_sid == d.name_sid;
  result = result && description_sid == d.description_sid;
  result = result && short_description_sid == d.short_description_sid;
  result = result && anger_message_sid == d.anger_message_sid;
  result = result && death_message_sid == d.death_message_sid;
  result = result && alignment_range == d.alignment_range;
  result = result && crowning_gifts == d.crowning_gifts;
  result = result && pct_chance_class_crowning == d.pct_chance_class_crowning;
  result = result && summons == d.summons;
  result = result && worship_site_type == d.worship_site_type;
  result = result && anger_script == d.anger_script;
  result = result && initial_modifier == d.initial_modifier;
  result = result && dislikes == d.dislikes;
  result = result && likes == d.likes;
  result = result && burial_races == d.burial_races;
  result = result && user_playable == d.user_playable;
  result = result && generator_filters == d.generator_filters;

  return result;
}

// Set/get the deity's internal identifier.
void Deity::set_id(const string& new_id)
{
  id = new_id;
}

string Deity::get_id() const
{
  return id;
}

// Set/get the deity's string ID for its name
void Deity::set_name_sid(const string& new_name_sid)
{
  name_sid = new_name_sid;
}

string Deity::get_name_sid() const
{
  return name_sid;
}

// Set/get the deity's string ID for its description (long form).
void Deity::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

string Deity::get_description_sid() const
{
  return description_sid;
}

// Set/get the deity's string ID for its short description (used on character creation)
void Deity::set_short_description_sid(const string& new_short_description_sid)
{
  short_description_sid = new_short_description_sid;
}

string Deity::get_short_description_sid() const
{
  return short_description_sid;
}

// Set/get the deity's anger message, used when the player
// has misbehaved.
void Deity::set_anger_message_sid(const string& new_anger_message_sid)
{
  anger_message_sid = new_anger_message_sid;
}

string Deity::get_anger_message_sid() const
{
  return anger_message_sid;
}

// Set/get the deity's death message.  This is displayed before "You die..."
void Deity::set_death_message_sid(const string& new_death_message_sid)
{
  death_message_sid = new_death_message_sid;
}

string Deity::get_death_message_sid() const
{
  return death_message_sid;
}

// Set/get the deity's alignment range
void Deity::set_alignment_range(const AlignmentRange new_alignment_range)
{
  alignment_range = new_alignment_range;
}

AlignmentRange Deity::get_alignment_range() const
{
  return alignment_range;
}

// Set/get a particular dislike
void Deity::set_dislike(const string& dislike, const bool value)
{
  dislikes.set_action_value(dislike, value);
}

bool Deity::get_dislike(const string& dislike) const
{
  return dislikes.get_action_value(dislike);
}

// Set/get a particular like
void Deity::set_like(const string& like, const bool value)
{
  likes.set_action_value(like, value);
}

bool Deity::get_like(const string& like) const
{
  return likes.get_action_value(like);
}

// Set/get the races the deity cares about for burial
void Deity::set_burial_races(const vector<string>& new_burial_races)
{
  burial_races = new_burial_races;
}

vector<string> Deity::get_burial_races() const
{
  return burial_races;
}
// Set/get the deity's list of crowning gifts.
void Deity::set_crowning_gifts(const vector<string>& new_crowning_gifts)
{
  crowning_gifts = new_crowning_gifts;
}

vector<string> Deity::get_crowning_gifts() const
{
  return crowning_gifts;
}

void Deity::set_pct_chance_class_crowning(const int new_pct_chance_class_crowning)
{
  pct_chance_class_crowning = new_pct_chance_class_crowning;
}

int Deity::get_pct_chance_class_crowning() const
{
  return pct_chance_class_crowning;
}

void Deity::set_summons(const vector<string>& new_summons)
{
  summons = new_summons;
}

vector<string> Deity::get_summons() const
{
  return summons;
}

// Set/get the worship site type.
void Deity::set_worship_site_type(const WorshipSiteType new_worship_site_type)
{
  worship_site_type = new_worship_site_type;
}

WorshipSiteType Deity::get_worship_site_type() const
{
  return worship_site_type;
}

// Set/get the Lua script invoked when the deity is angered.
void Deity::set_anger_script(const string& new_anger_script)
{
  anger_script = new_anger_script;
}

string Deity::get_anger_script() const
{
  return anger_script;
}

void Deity::set_initial_modifier(const Modifier& new_initial_modifier)
{
  initial_modifier = new_initial_modifier;
}

Modifier Deity::get_initial_modifier() const
{
  return initial_modifier;
}

void Deity::set_user_playable(const bool new_user_playable)
{
  user_playable = new_user_playable;
}

bool Deity::get_user_playable() const
{
  return user_playable;
}

void Deity::set_generator_filters(const vector<string>& new_generator_filters)
{
  generator_filters = new_generator_filters;
}

vector<string> Deity::get_generator_filters() const
{
  return generator_filters;
}

bool Deity::serialize(ostream& stream) const
{
  Serialize::write_string(stream, id);
  Serialize::write_string(stream, name_sid);
  Serialize::write_string(stream, description_sid);
  Serialize::write_string(stream, short_description_sid);
  Serialize::write_string(stream, anger_message_sid);
  Serialize::write_string(stream, death_message_sid);
  Serialize::write_enum(stream, alignment_range);
  Serialize::write_string_vector(stream, crowning_gifts);
  Serialize::write_int(stream, pct_chance_class_crowning);
  Serialize::write_string_vector(stream, summons);
  Serialize::write_enum(stream, worship_site_type);
  Serialize::write_string(stream, anger_script);

  initial_modifier.serialize(stream);
  dislikes.serialize(stream);
  likes.serialize(stream);
  Serialize::write_string_vector(stream, burial_races);
  Serialize::write_bool(stream, user_playable);
  Serialize::write_string_vector(stream, generator_filters);

  return true;
}

bool Deity::deserialize(istream& stream)
{
  Serialize::read_string(stream, id);
  Serialize::read_string(stream, name_sid);
  Serialize::read_string(stream, description_sid);
  Serialize::read_string(stream, short_description_sid);
  Serialize::read_string(stream, anger_message_sid);
  Serialize::read_string(stream, death_message_sid);
  Serialize::read_enum(stream, alignment_range);
  Serialize::read_string_vector(stream, crowning_gifts);
  Serialize::read_int(stream, pct_chance_class_crowning);
  Serialize::read_string_vector(stream, summons);
  Serialize::read_enum(stream, worship_site_type);
  Serialize::read_string(stream, anger_script);

  initial_modifier.deserialize(stream);
  dislikes.deserialize(stream);
  likes.deserialize(stream);
  Serialize::read_string_vector(stream, burial_races);
  Serialize::read_bool(stream, user_playable);
  Serialize::read_string_vector(stream, generator_filters);

  return true;
}

ClassIdentifier Deity::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DEITY;
}

#ifdef UNIT_TESTS
#include "unit_tests/Deity_test.cpp"
#endif
