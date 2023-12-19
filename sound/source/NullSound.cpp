#include "NullSound.hpp"

using namespace std;

NullSound::NullSound()
{
}

NullSound::~NullSound()
{
}

void NullSound::play(const string& path)
{
}

ClassIdentifier NullSound::internal_class_identifier() const
{
	return ClassIdentifier::CLASS_ID_NULL_SOUND;
}

#ifdef UNIT_TESTS
#include "unit_tests/NullSound_test.cpp"
#endif