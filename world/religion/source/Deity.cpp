#include "Deity.hpp"

using std::string;

Deity::Deity()
: alignment_range(ALIGNMENT_RANGE_NEUTRAL), worship_site_type(WORSHIP_SITE_CATHEDRAL)
{
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

// Set/get the worship site type.
void Deity::set_worship_site_type(const WorshipSiteType new_worship_site_type)
{
  worship_site_type = new_worship_site_type;
}

WorshipSiteType Deity::get_worship_site_type() const
{
  return worship_site_type;
}

void Deity::set_initial_statistics_modifier(const StatisticsModifier& new_initial_statistics_modifier)
{
  initial_statistics_modifier = new_initial_statistics_modifier;
}

StatisticsModifier Deity::get_initial_statistics_modifier() const
{
  return initial_statistics_modifier;
}
