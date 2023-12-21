#include "NullSound.hpp"

using namespace std;

NullSound::NullSound()
{
}

NullSound::~NullSound()
{
}

void NullSound::set_effects(const map<string, string>& new_effects)
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