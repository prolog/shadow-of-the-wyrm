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

void NullSound::set_disabled_sound_ids(const string& new_disabled_ids_csv)
{
}

void NullSound::play(const string& id)
{
}

ClassIdentifier NullSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_NULL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/NullSound_test.cpp"
#endif