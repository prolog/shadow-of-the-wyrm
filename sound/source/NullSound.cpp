#include "NullSound.hpp"

using namespace std;

NullSound::NullSound()
{
}

NullSound::~NullSound()
{
}

void NullSound::set_effects(const map<pair<string, string>, string>& new_effects)
{
}

void NullSound::set_music(const Music& new_music)
{
}

Music NullSound::get_music() const
{
	Music m;
	return m;
}

void NullSound::set_disabled_sound_ids(const string& new_disabled_ids_csv)
{
}

void NullSound::toggle_music(const bool new_val)
{
}

void NullSound::play(const string& id)
{
}

void NullSound::play_music_for_event(const string& event)
{
}

void NullSound::play_music(MapPtr map)
{
}

void NullSound::play_music_location(const string& location)
{
}

void NullSound::stop_music(const bool fade)
{
}

string NullSound::get_playing_music_location() const
{
	string no_music;
	return no_music;
}

ClassIdentifier NullSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_NULL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/NullSound_test.cpp"
#endif